# Enter Debug Simulator Mode:
1.) Change cursor setting in component.css file. It's currently set to none.
2.) Change DevMode flag and debug flag to true on the top of electron.js

# Compatible Versions of Firmware/Software as of 8/10/2020
Controller Firmware: 0.2.8
Relay Firmware:      0.1.7
SOM Software:        0.4.2

# Software-Feniex_One-Controller
Feniex one Controller 3.2 inch screen

## Building
## Building for Production
Make sure DevMode in electron.js is turned to false<br />

```bash
$ npm install
$ export USE_SYSTEM_FPM="true"
$ npm run electron-pack
$ cd dist
$ ar -x ./electron-react_0.1.0_armv7l.deb
$ tar Cxf / data.tar.xz
$ (optional if not run as root) chown -R ubuntu /opt/elecron-react
$ crontab -e
```
Uncomment out last line with the #<br />

Install AWS Iot Python SDK
```bash
$ python3 -m pip install AWSIoTPythonSDK
```

Save file
```bash
$ reboot
```

Versions working on 18.04 Desktop
```bash
Highest working node - 12.6.0 (possible issues with serial port)
controller node version - 11.15.0
Use yarn to install react-scripts -> run yarn to install node_modules
yarn working react scripts react-scripts 3.4.4
electron - 6.0.12
```

Build Issue Bug Solutions:
https://github.com/electron-userland/electron-builder/issues/3901

Make sure fpm is installed or symlinked in /usr/bin directory
```bash
ls /usr/bin
```
if not, install then symlink
```bash
gem install --no-document fpm
ln -s /usr/bin/fpm/fpm.ruby2.5 /usr/bin/fpm
```
then before build run:
```bash
export USE_SYSTEM_FPM="true"
```
Change Audio Volume:
```bash
amixer scontrols
amixer sset 'Headphone' 100%
```
Connecting to WIFI
```bash
nmcli d wifi connect <EnterSSIDHere> password <EnterPasswordHere> ifname <DeviceName>
```
Device name is usually wlan0

Reset Commit after trying to commit too large of file for node_modules/ and/or dist/
```bash
$ git rm -rf node_modules (This will delete the node_module folder from you project folder too.)
$ git reset --soft HEAD^
$ git add .
$ git commit -m "<Insert commit notes here.>"
$ git push origin master
```

mksquash issue:
https://github.com/electron-userland/electron-builder-binaries/issues/20

### Login
User: pluto<br />
Password: Teamwork makes The dream Work!!!<br />
