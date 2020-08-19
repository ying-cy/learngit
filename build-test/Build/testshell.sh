

if [ -d "NextEngine/" ];then
    echo "NextEngine repository exists"
else
    echo "NextEngine repository does not exist"
    echo "Start to git clone ..."
    git clone http://git.code.oa.com/IEG-RED-GameEngine/NextEngine.git
    
    cd NextEngine
    git checkout develop/CrossEngine-QQ
    cd ../
fi

cd NextEngine/Build
chmod -R 777 ./

sh ./Git_Pull_develop_CrossEngine-QQ.sh
