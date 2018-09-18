# Interactive-Video for Citizen Rotation Office

## Videos
The videos are not included in this repo because they're too big!

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
