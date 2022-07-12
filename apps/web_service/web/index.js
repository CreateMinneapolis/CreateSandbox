import * as THREE from './src/js/threeJS/three.module.js';
import { OrbitControls } from './src/js/threeJS/OrbitControls.js';
import { GLTFLoader } from './src/js/threeJS/GLTFLoader.js';

//lets us talk to our c++ backend. This is from the WSApi file in src/js
let api = new WSApi();
let entities = {}
let entityList = [];
let models = [];
const group = new THREE.Group();
//add utils
let camera, renderer;
const scene =  new THREE.Scene();
let container = document.querySelector( '#scene-container' );
const mixers = [];
// const scene = new THREE.Scene()
const loader = new GLTFLoader();
const clock = new THREE.Clock();
// const renderer = new THREE.WebGLRenderer()

let time = 0.0;
let simSpeed = 1.0;
$( document ).ready(function() {
	init()
	window.addEventListener( 'resize', onWindowResize );
	
	try {
		api.onmessage = function(msg, data) {
			
			if(data.event != null){
				if(data.event == "AddEntity"){
					console.log(`Adding entity of type ${data.details.details.type} to the scene`);
					AddEntity(data.details.details)
				}
				if(data.event == "UpdateEntity"){
					UpdateEntity(data.details);
				}
			}
		}
	}
	catch(excetion) {
		alert(excetion)
	}
});

//Init function initalizes the scene and lets it get called
// on document.ready so it can load before everything else
function init() {
	const fov = 35; // fov = Field Of View
	const aspect = container.clientWidth / container.clientHeight;
	const near = 0.1;
	const far = 5000;

	//Add camera
	camera = new THREE.PerspectiveCamera( fov, aspect, near, far );
	camera.position.set( 9, 2, -4 );
	// controls = new OrbitControls( camera, container );

	//Add Scene
	scene.background = new THREE.Color( 'skyblue' );


	//add controls so you can click and drag to move around
	// controls.enableDamping = true
	// controls.target.set(0, 1, 0)

	//Set light sources
	const ambientLight = new THREE.AmbientLight( 0xffffff, 1 );
	scene.add( ambientLight );
	const light = new THREE.DirectionalLight( 0xffffff, 0.5 );
	light.position.set( 10, 10, 10 );
	scene.add( ambientLight, light );
	const light2 = new THREE.DirectionalLight( 0xffffff, 0.5 );
	light2.position.set( 0, 10, -10 );
	scene.add( ambientLight, light2 );

	renderer = new THREE.WebGLRenderer( { antialias: true, logarithmicDepthBuffer: true, } );
	renderer.setSize( window.innerWidth, window.innerHeight );
	document.body.appendChild( renderer.domElement );
	
	//this will set the scene with all the commands laid out in scene.json
	$.getJSON("./scene.json", function(json) {
		for(let i = 0; i < json.length; i++){
			if(json[i].command == "AddMesh"){
				loader.load( json[i].params.mesh, function ( glb ) {
					const pos = new THREE.Vector3(json[i].params.position[0], json[i].params.position[1], json[i].params.position[2])
					const tempScale = new THREE.Vector3(json[i].params.scale[0], json[i].params.scale[1], json[i].params.scale[2])
					glb.scene.scale.copy(tempScale)
					glb.scene.position.copy(pos)
					
					scene.add(glb.scene)
				}, undefined, function ( error ) {
					console.error( error );
				} );
				//handle updates for animations
				renderer.setAnimationLoop( () => {
					update();
					render();
				});
			}else {
				api.sendCommand(json[i].command, {entityId: i, type: json[i].params.type, name: json[i].params.name, mesh: json[i].params.mesh, position: json[i].params.position});
			}
			
		}
	})
}

function AddEntity(details) {
	const position = [details.position[0], details.position[1], details.position[2]];
	const id = details.id;
	let mesh = details.mesh;
	LoadModel(mesh, id, position, [0,0,0]);
}

function UpdateEntity(details){
	if(entities[details.id] != undefined){
		let model = entities[details.id];

		model.position.x = details.pos[0];
		model.position.y = details.pos[1];
		model.position.z = details.pos[2];
		
		const dir = new THREE.Vector3(details.dir[0], details.dir[1], details.dir[2]);

		let vector = new THREE.Vector3( 0, 1, 0 );
		vector = model.worldToLocal(vector);

		const adjustedDirVector = model.localToWorld(new THREE.Vector3(0,0,0)).add(dir);
        model.lookAt(adjustedDirVector);

		camera.lookAt(model.position)
	}
}
function LoadModel(mesh, id, position, scale){
	loader.load( mesh, function ( glb ) {
		const model = glb.scene.children[0]

		const pos = new THREE.Vector3(position[0], position[1], position[2])
		const tempScale = new THREE.Vector3(scale[0], scale[1], scale[2])
		glb.scene.scale.copy(tempScale)
		model.position.copy(pos)
		const animation = glb.animations[0];
		
		if (!(typeof animation === "undefined")) {
		  const mixer = new THREE.AnimationMixer( model );
		  mixers.push( {id: id, mixer: mixer, start: 0, duration: glb.duration} );
		var action = mixer.clipAction(animation);
			action.play();
		}

		group.add(model);
		group.position.copy(pos);

		models.push(group);
		scene.add( group );
		entities[id] = group;
		entityList.push(id);
	}, undefined, function ( error ) {
		console.error( error );
	} );


	//handle updates for animations
	renderer.setAnimationLoop( () => {
		update();
		render();
	});
}

function render() {
	renderer.render( scene, camera );
}

// This function updates the scene's animation cycle.
function update() {
	// Get the time since the last animation frame.
	const delta = clock.getDelta();
	time += delta;
  
	// Iterate through and update the animation mixers for each object in the
	// scene.
	for ( const mixer of mixers ) {
		if (mixer.start == undefined || mixer.duration == undefined) {
		  mixer.mixer.update(delta);
		}
		else {
		  var newTime = time - mixer.start;
		  var iterations = Math.floor(newTime/mixer.duration);
		  newTime = newTime - iterations*mixer.duration + mixer.start;
		  mixer.mixer.setTime(newTime);
		}
	}
	//This is where we can send the update command that our c++ backend will talk to
	//comments out now cause its annoying
	api.sendCommand("update", { simSpeed: simSpeed })

}

function onWindowResize() {
	// set the aspect ratio to match the new browser window aspect ratio
	camera.aspect = window.innerWidth / window.innerHeight;
  
	// update the camera's frustum
	camera.updateProjectionMatrix();
  
	// update the size of the renderer AND the canvas
	renderer.setSize(window.innerWidth, window.innerHeight);
  }

