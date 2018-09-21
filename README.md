# Interactive Video Player
This project uses a kinect and custom video generator to play randomised video sequences each time a person is detected in front of the display.

## Videos
The videos are not included in this repo because they're too big!

They were exported as Quicktime files with the Animation codec, to ensure they're full quality. Then I followed the [encoding guide](https://gist.github.com/dlublin/e4585b872dd136ae88b2aa51a6a89aac) to encode the videos as HAP using ffmpeg through the command line.

## Compiling
To ensure the video files are included in the bundle there's a script that is used in xcode.
```
1. Click on your project in the Project Navigator
2. Select "Build Phases"
3. Toggle open the "Run Script" section and paste in the following:
cp -r bin/data "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources";
```
Then you should use the follow code inside the openFrameworks project to override the path to the data folder.
```
ofSetDataPathRoot("../Resources/data/");
```
You will also need to install [Hap QuickTime Codec version 12](https://github.com/vidvox/hap-qt-codec/releases/) on any machine you want to run the app, because this uses the [HAP codec](http://hap.video/) to play videos directly on GPU and make massive performance gains.

You will also need to compile to 32-bit as HAP uses Quicktime which doesn't run 64-bit.

## Contributing
Download the repo and create a new branch from the master, then when a new version is ready and fully tested, you should push the new branch to GitHub and create a pull request. We do not push directly into the origin/master branch.
