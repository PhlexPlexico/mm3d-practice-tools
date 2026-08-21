#pragma once
#include "common/types.h"
#include "z3d/z3DVec.h"
namespace game::cmb {
  struct RGBA {
    u8 R, G, B, A;

    constexpr RGBA() : R(0), G(0), B(0), A(0) {}
    constexpr RGBA(u8 r, u8 g, u8 b, u8 a) : R(r), G(g), B(b), A(a) {}
    constexpr RGBA(u32 c) : R(u8(c >> 24)), G(u8(c >> 16)), B(u8(c >> 8)), A(u8(c)) {}
  };

  enum class BlendModes : u8 { BlendNone, Blend, BlendSeparate, LogicalOp };

  enum class FresnelSelector : u16 { No = 0x62C0, Pri = 0x62C1, Sec = 0x62C2, PriSec = 0x62C3 };

  enum class DataTypes : u16 {
    Byte = 0x1400,
    UByte = 0x1401,
    Short = 0x1402,
    UShort = 0x1403,
    Int = 0x1404,
    UInt = 0x1405,
    Float = 0x1406
  };

  enum class TestFunc : u16 {
    Never = 0x200,
    Less = 0x201,
    Equal = 0x202,
    Lequal = 0x203,
    Greater = 0x204,
    Notequal = 0x205,
    Gequal = 0x206,
    Always = 0x207
  };

  enum class BlendFunc : u16 {
    Zero = 0x0,
    One = 0x1,
    SourceColor = 0x300,
    OneMinusSourceColor = 0x301,
    SourceAlpha = 0x302,
    OneMinusSourceAlpha = 0x303,
    DestinationAlpha = 0x304,
    OneMinusDestinationAlpha = 0x305,
    DestinationColor = 0x306,
    OneMinusDestinationColor = 0x307,
    SourceAlphaSaturate = 0x308,
    ConstantColor = 0x8001,
    OneMinusConstantColor = 0x8002,
    ConstantAlpha = 0x8003,
    OneMinusConstantAlpha = 0x8004
  };

  enum class BlendEquation : u32 {
    FuncAdd = 0x8006,
    Min = 0x8007,
    Max = 0x8008,
    FuncSubtract = 0x800A,
    FuncReverseSubtract = 0x800B
  };

  enum class FaceCulling : u8 { FrontAndBack, Front, BackFace, None };

  enum class BumpTextures : u16 { Texture0 = 0x84C0, Texture1 = 0x84C1, Texture2 = 0x84C2 };

  enum class BumpModes : u16 { NotUsed = 0x62C8, AsBump = 0x62C9, AsTangent = 0x62CA };

  enum class Modes : u16 { Array, Constant };

  enum class SkinningModes : u16 { Mixed, Rigid, Smooth };

  enum class LUTInput : u16 {
    CosNormalHalf = 0x62A0,
    CosViewHalf = 0x62A1,
    CosNormalView = 0x62A2,
    CosLightNormal = 0x62A3,
    CosLightSpot = 0x62A4,
    CosPhi = 0x62A5
  };

  enum class LayerConfig : u16 {
    LayerConfig0 = 0x62B0,
    LayerConfig1 = 0x62B1,
    LayerConfig2 = 0x62B2,
    LayerConfig3 = 0x62B3,
    LayerConfig4 = 0x62B4,
    LayerConfig5 = 0x62B5,
    LayerConfig6 = 0x62B6,
    LayerConfig7 = 0x62B7
  };

  enum class CombinerOp : u16 {
    Color = 0x0300,
    OneMinusColor = 0x0301,
    Alpha = 0x0302,
    OneMinusAlpha = 0x0303,
    Red = 0x8580,
    Green = 0x8581,
    Blue = 0x8582,
    OneMinusRed = 0x8583,
    OneMinusGreen = 0x8584,
    OneMinusBlue = 0x8585
  };

  enum class CombinerMode : u16 {
    Replace = 0x1E01,
    Modulate = 0x2100,
    Add = 0x0104,
    AddSigned = 0x8574,
    Interpolate = 0x8575,
    Subtract = 0x84E7,
    DotProduct3Rgb = 0x86AE,
    DotProduct3Rgba = 0x86AF,
    MultAdd = 0x6401,
    AddMult = 0x6402
  };

  enum class CombinerSrc : u16 {
    PrimaryColor = 0x8577,
    FragmentPrimaryColor = 0x6210,
    FragmentSecondaryColor = 0x6211,
    Texture_0 = 0x84C0,
    Texture_1 = 0x84C1,
    Texture_2 = 0x84C2,
    Texture_3 = 0x84C3,
    PreviousBuffer = 0x8579,
    ConstantCol = 0x8576,
    Previous = 0x8578
  };

  enum class CombinerScale {
    _One = 1,
    _Two = 2,
    _Four = 4,
  };

  enum class TextureFormatGL : u32 {
    ETC1 = 0x0000675A,
    ETC1A4 = 0x0000675B,
    RGB8 = 0x14016754,
    RGBA8 = 0x14016752,
    RGBA4444 = 0x80336752,
    RGBA5551 = 0x80346752,
    RGB565 = 0x83636754,
    A8 = 0x14016756,
    A4 = 0x67616756,
    L8 = 0x14016757,
    L4 = 0x67616757,
    LA8 = 0x14016758,
    LA4 = 0x67606758,
    HILO8 = 0x14016759,
  };

  struct Bone {
    u16 index;
    // 4095 is the max value (In MM3D anyway)
    // (Value & 0xFFF) to get the bone ID
    // But what is the flag?
    s16 parentIndex;
    z3dVec3f scale;
    z3dVec3f rotation;
    z3dVec3f translation;
  };
  static_assert(sizeof(Bone) == 0x28);

  struct Skeleton {
    char magic[4];
    u32 size;
    u32 boneCount;
    u32 unk;
    Bone bone[];
  };
  static_assert(sizeof(Skeleton) == 0x10);

  struct Combiner {
    CombinerMode combinerModeColor;
    CombinerMode combinerModeAlpha;
    CombinerScale scaleColor;
    CombinerScale scaleAlpha;
    CombinerSrc bufferColor;
    CombinerSrc bufferAlpha;
    // Color
    CombinerSrc sourceColor0;
    CombinerSrc sourceColor1;
    CombinerSrc sourceColor2;
    // Color
    CombinerOp operandColor0;
    CombinerOp operandColor1;
    CombinerOp operandColor2;
    // Alpha
    CombinerSrc sourceAlpha0;
    CombinerSrc sourceAlpha1;
    CombinerSrc sourceAlpha2;
    // Alpha
    CombinerOp operandAlpha0;
    CombinerOp operandAlpha1;
    CombinerOp operandAlpha2;
    u32 constantIndex;
  };
  static_assert(sizeof(Combiner) == 0x2C);

  struct TextureMapper {
    s16 textureID;
    u16 unk_02;  // Padding?
    u16 textureMinFilter;
    u16 textureMagFilter;
    u16 textureWrapModes;
    u16 textureWrapModet;
    f32 minLODBias;
    f32 lodBias;
    RGBA BorderColor;
  };
  static_assert(sizeof(TextureMapper) == 0x18);

  struct TextureCoord {
    u8 coordinateIndex;
    u8 referenceCamera;
    u8 mappingMethod;
    u8 matrixMode;
    z3dVec2f scale;
    z3dVec2f translation;
    f32 rotation;
  };
  static_assert(sizeof(TextureCoord) == 0x18);

  struct Sampler {
    bool isAbs;
    s8 index;
    LUTInput input;
    f32 scale;
  };
  static_assert(sizeof(Sampler) == 0x08);

  struct Fragment {
    LayerConfig config;
    __attribute__((packed)) __attribute__((aligned(4))) FresnelSelector selector;

    bool isClampHighLight;
    bool isDistribution0Enabled;
    bool isDistribution1Enabled;
    bool isGeometricFactor0Enabled;
    bool isGeometricFactor1Enabled;
    bool isReflectionEnabled;

    Sampler distibution0Sampler;
    Sampler distibution1Sampler;
    Sampler reflectanceRSampler;
    Sampler reflectanceGSampler;
    Sampler reflectanceBSampler;
    Sampler fresnelSampler;
  };
  static_assert(sizeof(Fragment) == 0x3C);

  struct Material {
    bool isFragmentLightingEnabled;
    bool isVertexLightingEnabled;
    bool IsFogEnabled;
    u8 renderLayer;  // Opaque, Translucent, Subtractive blending, Additive blending.

    FaceCulling culling;

    bool isPolygonOffsetEnabled;
    s16 polygonOffsetValue;

    u32 textureMappersUsed;
    u32 textureCoordsUsed;

    TextureMapper textureMappers[3];
    TextureCoord textureCoords[3];

    RGBA emissionColor;
    RGBA ambientColor;
    RGBA diffuse;
    RGBA specular0;
    RGBA specular1;
    RGBA constantColors[6];

    z3dVec4f BufferColor;

    BumpTextures bumpTexture;
    BumpModes bumpMode;
    bool isBumpRenormalize;

    __attribute__((packed)) __attribute__((aligned(4))) Fragment fragLighting;

    u32 texEnvStageUsed;
    s16 texEnvStagesIndices[6];

    bool alphaTestEnabled;
    u8 alphaTestReferenceValue;
    TestFunc alphaTestFunction;

    bool depthTestEnabled;
    bool depthWriteEnabled;
    TestFunc depthTestFunction;

    BlendModes dlendMode;

    __attribute__((packed)) __attribute__((aligned(4))) BlendFunc colorSrcFunc;
    BlendFunc colorDstFunc;
    BlendEquation colorEquation;
    BlendFunc alphaSrcFunc;
    BlendFunc alphaDstFunc;
    BlendEquation alphaEquation;

    z3dVec4f blendColor;

    s8 stencilEnabled;
    s8 stencilReferenceValue;
    u16 mask;
    u16 stencilFunc;
    u16 failOP;
    u16 zFailOP;
    u16 zPassOP;
    u32 unkHash;
  };
  static_assert(sizeof(Material) == 0x16C);

  struct Mats {
    char magic[4];
    u32 size;
    u32 materialCount;
    game::cmb::Material material[];
    // game::cmb::Combiner Combiner[]; // Commented out as we cannot have two flexible arrays in a single struct.
  };
  static_assert(sizeof(Mats) == 0x0C);

  struct TextureEntry {
    u32 dataLength;
    u16 mipMapCount;
    u8 isETC1;
    u8 isCubemap;  // Padding in OoT3D/MM3D?
    u16 width;
    u16 height;
    union {
      struct {
        u16 imageFormat;
        u16 dataType;
      };
    };
    u16 dataOffset;
    char name[16];
  };
  static_assert(sizeof(TextureEntry) == 0x24);

  struct Tex {
    char magic[4];
    int size;
    int textureCount;
    TextureEntry entry[];
  };
  static_assert(sizeof(Tex) == 0x0C);

  struct Mesh {
    u16 sepdIndex;
    u8 materialIndex;
    u8 id;
    u32 unkHash0;
    u32 unkHash1;
  };
  static_assert(sizeof(Mesh) == 0x0C);

  struct IdxStream {
    u32 primitiveMode;
    DataTypes indexType;
    u8 unk00;
    u8 unkFF;
    u16 indicesCount;
    u16 offset;
  };
  static_assert(sizeof(IdxStream) == 0xC);

  struct PRM {
    char magic[4];
    u32 size;
    u32 indexStreamCount;
    IdxStream stream;
  };
  static_assert(sizeof(PRM) == 0x18);

  struct PrmSet {
    SkinningModes skinningMode;
    u16 boneTableCount;
    int boneTableOffset;
    int primOffset;

    s16 boneIndices[];
    // PRM prm[]; //Commented out as we cannot have two flexible arrays in a single struct.
  };
  static_assert(sizeof(PrmSet) == 0x0C);

  struct PRMS {
    char magic[4];
    int size;
    int prmCount;
    PrmSet PRMs[];
  };
  static_assert(sizeof(PRMS) == 0x0C);

  struct Attribute {
    int start;
    f32 scale;
    DataTypes dataType;
    Modes mode;
    z3dVec4f constants;
  };
  static_assert(sizeof(Attribute) == 0x1C);

  struct SEPD {
    char magic[4];
    u32 size;
    u16 prmsCount;

    u16 hasPosition;
    u16 hasNormals;
    u16 hasColor;
    u16 hasUV0;
    u16 hasUV1;
    u16 hasUV2;
    u16 hasIndices;
    u16 hasWeights;

    z3dVec3f meshCenter;
    z3dVec3f positionOffset;

    Attribute position;
    Attribute normals;
    Attribute tangents;
    Attribute colors;
    Attribute uv0;
    Attribute uv1;
    Attribute uv2;
    Attribute indices;
    Attribute weights;

    u16 boneDimensionCount;
    u16 usedConstantFlags;  // Bitflags for when an attribute uses contants values
    u16 prmsOffsets[];

    // Variable amount of PRMs.
    // PRMS prm;
  };
  static_assert(sizeof(SEPD) == 0x134);

  struct CMB_MSHS {
    char magic[4];
    u32 size;
    u32 meshCount;
    u16 opaqueMeshCount;  // The remainder of "OpaqueMeshCount" are transparent meshes
    u16 idCount;
    Mesh meshes[];
  };
  static_assert(sizeof(CMB_MSHS) == 0x10);

  struct CMB_SHP {
    char magic[4];
    u32 size;
    u32 sepdCount;
    u32 flags;
    // Variable amount of SEPDs.
    // SEPD sepd;
  };
  static_assert(sizeof(CMB_MSHS) == 0x10);

  struct CMB_HEAD {
    char magic[4];
    u32 size;
    u32 version;
    u32 unk_0C;
    char name[16];
    u32 faceIndicesCount;
    u32 sklOffset;
    u32 qtrsOffset;
    u32 matsOffset;
    u32 texOffset;
    u32 sklmOffset;
    u32 lutsOffset;
    u32 vatrOffset;
    u32 faceIndicesOffset;
    u32 textureDataOffset;
    u32 unk_48;
  };
  static_assert(sizeof(CMB_HEAD) == 0x4C);

  struct CMB_SKLM {
    char magic[4];
    u32 size;
    u32 mshsOffset;
    u32 shpOffset;
    CMB_MSHS mshs;
    // CMB_SHP shp; // Meshes variable array is at the end of mshs so comment this out.
  };

  static inline Mats* Cmb_GetMatsChunk(void* cmb) {
    return (Mats*)(((u32)cmb) + ((CMB_HEAD*)cmb)->matsOffset);
  }

  static inline Material* Cmb_GetMaterial(void* cmb, u32 index) {
    Mats* mats = Cmb_GetMatsChunk(cmb);
    if (mats == nullptr || index >= mats->materialCount)
      return nullptr;
    return &mats->material[index];
  }

}  // namespace game::cmb