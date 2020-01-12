read -p "Check all paths in script, run simulator or connect android device before continue..."
PATH="/home/demensdeum/Android/Sdk/ndk/20.1.5948944/:$PATH"                   # for 'ndk-build'
PATH="/home/demensdeum/Android/Sdk/tools/:$PATH"           # for 'android'
PATH="/home/demensdeum/Android/Sdk/platform-tools/:$PATH"  # for 'adb'
export ANDROID_HOME="/home/demensdeum/Android/Sdk/"        # for gradle
export ANDROID_NDK_HOME="/home/demensdeum/Android/Sdk/ndk/20.1.5948944/"      # for gradle 
cd /home/demensdeum/Sources/SDL2/build-scripts/
./androidbuild.sh org.libsdl.testgles /home/demensdeum/Sources/android-sdl-test-app/main.c
cd /home/demensdeum/Sources/SDL2/build/org.libsdl.testgles
./gradlew installDebug --stacktrace --info
read -p "There must be \"Game\" app with SDL icon on simulator or android device..."
exit 0
