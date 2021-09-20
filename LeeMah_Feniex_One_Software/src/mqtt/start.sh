# stop script on error
set -e

# Check to see if root CA file exists, download if not
if [ ! -f ./root-CA.crt ]; then
  printf "\nDownloading AWS IoT Root CA certificate from AWS...\n"
  curl https://www.amazontrust.com/repository/AmazonRootCA1.pem > root-CA.crt
fi

# Check to see if AWS Device SDK for Python exists, download if not
if [ ! -d ./aws-iot-device-sdk-python ]; then
  printf "\nCloning the AWS SDK...\n"
  git clone https://github.com/aws/aws-iot-device-sdk-python.git
fi

# Check to see if AWS Device SDK for Python is already installed, install if not
if ! python -c "import AWSIoTPythonSDK" &> /dev/null; then
  printf "\nInstalling AWS SDK...\n"
  pushd aws-iot-device-sdk-python
  python setup.py install
  result=$?
  popd
  if [ $result -ne 0 ]; then
    printf "\nERROR: Failed to install SDK.\n"
    exit $result
  fi
fi

# run pub/sub sample app using certificates downloaded in package
printf "\nRunning pub/sub sample application...\n"
python aws-iot-device-sdk-python/samples/basicPubSub/basicPubSub.py -e a2mmua2sxz1lo6-ats.iot.us-east-1.amazonaws.com -r root-CA.crt -c Feniex_Controllers.cert.pem -k Feniex_Controllers.private.key


          let updateMqtt = JSON.parse(mqttPayload);
            updateMqtt.Temperature = tempHigh;
            mqttPayload = JSON.stringify(updateMqtt);


 let func = () => {
   const child = childProcess.fork(path, args, 
   {
     silent: true,
     detached: true, 
     stdio: 'ignore',
   }

 });

 child.on('error', (err) => {
   console.log("\n\t\tERROR: spawn failed! (" + err + ")");
 });

 child.stderr.on('data', function(data) {
   console.log('stdout: ' +data);
 });

 child.on('exit', (code, signal) => {
   console.log(code);
   console.log(signal);
 });

 child.unref();
