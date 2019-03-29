# InteractiveVideo
This project uses a kinect and custom video generator to play randomised video sequences each time a person is detected in front of the display. The message from the kinect comes over OSC from the [KinectV2-Blob-Detection](https://github.com/hmcro/KinectV2-Blob-Detection) app.

## Building
To build this project you will need to use the projectGenerator in openFramework.

## Videos
The videos are not included in this repo because they're too big!

They were exported as Quicktime files with the Animation codec, to ensure they're full quality. Then I followed the [encoding guide](https://gist.github.com/dlublin/e4585b872dd136ae88b2aa51a6a89aac) to encode the videos as HAP using ffmpeg through the command line.

## Compiling
The use the HAP AVFoundation Codec player you must add 2 lines to the __Runpath Search Paths__ in __Build Settings__
```
@loader_path/../Frameworks
@executable_path/../Frameworks
```
## Tested
Currently working on:
- mac 10.4.3
- xcode 10.1
- openFrameworks 10.1
