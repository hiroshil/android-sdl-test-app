#ifndef FSEGTConst_defined
#define FSEGTConst_defined

#include <string>
using namespace std;

#define GameMapTileSize 64
#define FSEGTMaxSceneObjects 1024

enum
{
    FSEGTConstCeiling,
    FSEGTConstWall,
    FSEGTConstFloor
};

namespace FlameSteelEngine
{
namespace GameToolkit
{
namespace SceneLayer
{
enum
{
    Skybox,
    Scene,
    Screen
};
};
};
};

#define FSEGTConstTextureSize 64
#define FSEGT_MAX_TILES_COUNT 64

static const string FSEGTConstComponentsFlagSkybox = "FSEGTConstComponentsFlagSkybox";
static const string FSEGTConstComponentsFlag2D = "FSEGTConstComponentsFlag2D";
static const string FSEGTConstComponentsScale = "Scale";
static const string FSEGTConstComponentsPosition = "Position";
static const string FSEGTConstComponentsRotation = "Rotation";
static const string FSEGTConstComponentsEulerRotation = "Euler Rotation";
static const string FSEGTConstComponentsAI = "AI";
static const string FSEGTConstComponentsBrightness = "Brightness";
static const string FSEGTConstComponentsSprite = "Sprite";
static const string FSEGTConstComponentsSpeed = "Speed";
static const string FSEGTConstComponentsDeleted = "Deleted";
static const string FSEGTConstComponentsText = "Text";
static const string FSEGTConstComponentsModel = "3D Model";
static const string FSEGTConstComponentsSerializedModel = "3D Serialized Model";
static const string FSEGTConstComponentsRelativeScreenPosition = "Relative screen position";

static const string FSEGTConstObjectClassIdentifierOnScreenText = "On screen text";

#endif
