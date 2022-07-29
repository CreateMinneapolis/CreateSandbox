
git config --global --add safe.directory /home/user/repo
ROOTDIR=`git rev-parse --show-toplevel`


${ROOTDIR}/build/bin/WebService 8081 apps/web_service/web/


