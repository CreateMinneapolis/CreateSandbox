import * as THREE from './src/js/threeJS/three.module.js';
import { OrbitControls } from './src/js/threeJS/OrbitControls.js';
import { GLTFLoader } from './src/js/threeJS/GLTFLoader.js';

//lets us talk to our c++ backend. This is from the WSApi file in src/js
let api = new WSApi();

//add utils
var geometry, material, mesh;
var camera, scene, renderer, controls;
var container = document.querySelector( '#scene-container' );
const mixers = [];
// const scene = new THREE.Scene()
const loader = new GLTFLoader();
const clock = new THREE.Clock();
// const renderer = new THREE.WebGLRenderer()

var time = 0.0;
var simSpeed = 1.0;
$( document ).ready(function() {
	init()
	window.addEventListener( 'resize', onWindowResize );
});

//Init function initalizes the scene and lets it get called
// on document.ready so it can load before everything else
function init() {
	const fov = 35; // fov = Field Of View
	const aspect = container.clientWidth / container.clientHeight;
	const near = 0.1;
	const far = 1000;

	//Add camera
	camera = new THREE.PerspectiveCamera( fov, aspect, near, far );
	camera.position.set( 15, 15, 30 );
	controls = new OrbitControls( camera, container );

	//Add Scene
	scene = new THREE.Scene();
	scene.background = new THREE.Color( 'skyblue' );
	scene.add(new THREE.AxesHelper(5))

	//add controls so you can click and drag to move around
	controls.enableDamping = true
	controls.target.set(0, 1, 0)

	//Set light sources
	const ambientLight = new THREE.AmbientLight( 0xffffff, 1 );
	scene.add( ambientLight );
	const light = new THREE.DirectionalLight( 0xffffff, 1 );
	light.position.set( 10, 10, 10 );
	scene.add( ambientLight, light );
	const light2 = new THREE.DirectionalLight( 0xffffff, 1 );
	light2.position.set( 0, 10, -10 );
	scene.add( ambientLight, light2 );

	
	//load first model - move into function later
	let modelReady = false
	const animationActions = []
	let activeAction
	let lastAction
	let mixer

	renderer = new THREE.WebGLRenderer( { antialias: true } );
	renderer.setSize( window.innerWidth, window.innerHeight );
	document.body.appendChild( renderer.domElement );
	
	LoadModel('./src/assets/model/robot.glb', 0, [0,0,0])
	LoadModel('./src/assets/model/drone.glb', 0, [6,0,0])
}

function LoadModel(path, id, position){
	loader.load( path, function ( glb ) {
		
		glb.scene.position.x += position[0]
		glb.scene.position.y += position[1]
		glb.scene.position.z += position[2]
		const mixer = new THREE.AnimationMixer(glb.scene)
		
		const animation = glb.animations[0];
		console.log(animation)
		mixers.push({id: id, mixer: mixer, start: 0, duration: animation.duration})
		var action = mixer.clipAction(animation);
		action.play();
		scene.add(glb.scene)

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
	//api.sendCommand("Update", { simSpeed: simSpeed });
}

function onWindowResize() {
	// set the aspect ratio to match the new browser window aspect ratio
	camera.aspect = window.innerWidth / window.innerHeight;
  
	// update the camera's frustum
	camera.updateProjectionMatrix();
  
	// update the size of the renderer AND the canvas
	renderer.setSize(window.innerWidth, window.innerHeight);
  }
