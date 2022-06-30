
git config --global --add safe.directory /home/user/repo
ROOTDIR=`git rev-parse --show-toplevel`


${ROOTDIR}/build/bin/DroneSim 8081 apps/drone_sim/web/


