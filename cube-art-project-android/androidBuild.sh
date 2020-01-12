#rm -rf app/build || true
export ANDROID_HOME=/home/demensdeum/Android/Sdk/
export ANDROID_NDK_HOME=/home/demensdeum/Android/android-ndk-r21-beta2/
#./gradlew clean build
./gradlew installDebug 
