/**
MIT License
Copyright (c) 2016 bbqz007 <https://github.com/bbqz007, http://www.cnblogs.com/bbqzsl>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once
#ifndef _CA_namespace__H_
#define _CA_namespace__H_

namespace CA {
	void;

	struct Bounds;
	struct ColorMatrix;
	struct Context;
	struct DispatchGroup;
	struct GenericContext;
	struct Layer;
	struct RadixSortDoubleItem;
	struct RadixSortItem;
	struct Rect;
	struct Shape;
	struct ShapeHandle;
	struct Transaction;
	struct Transform;
	struct UnMat2;
	struct UnMat4;
	struct Volume;
	struct Context;
	struct ObjCBool;
	struct ObjCCAColorMatrix;
	struct ObjCCAPoint3D;
	struct ObjCCATransform3D;
	struct ObjCCGAffineTransform;
	struct ObjCCGColor;
	struct ObjCCGFont;
	struct ObjCCGImage;
	struct ObjCCGPDFDocument;
	struct ObjCCGPath;
	struct ObjCCGPoint;
	struct ObjCCGRect;
	struct ObjCCGSize;
	struct ObjCContext;
	struct ObjCInteger;
	struct ObjCNSArray;
	struct ObjCNSDictionary;
	struct ObjCNSObject;
	struct ObjCNSSet;
	struct ObjCNSURL;
	struct ObjCNull;
	struct ObjCReal;
	struct ObjCScript;
	struct ObjCString;
	struct ObjCType;
	struct State;
	struct StateName;
	struct Type;
	namespace Display {
		void;

		struct Display;
		struct DisplayLink;
		struct DisplayLinkItem;
		struct EmulatorDisplay;
		struct TimerDisplayLink;
	}
	namespace OGL {
		void;

		struct BackdropBuffer;
		struct BackdropNode;
		struct BlendFunction;
		struct BlendNode;
		struct CacheNode;
		struct Color;
		struct CombineNode;
		struct CompositeNode;
		struct ContentsGeometry;
		struct Context;
		struct ContextProperty;
		struct ContextState;
		struct DebugRenderer;
		struct Filter;
		struct FilterNode;
		struct GLContext;
		struct GLESContext;
		struct GLESImage;
		struct GLShader;
		struct Gstate;
		struct Image;
		struct ImageFunction;
		struct ImagingNode;
		struct Layer;
		struct LayerNode;
		struct MaskNode;
		struct MeshNode;
		struct MotionBlurNode;
		struct PingPongState;
		struct PrimitiveMode;
		struct QuadNode;
		struct Renderer;
		struct SWContext;
		struct SWImage;
		struct ShadowNode;
		struct SourceRequirement;
		struct Surface;
		struct TextureEdgeMode;
		struct TextureFilter;
		struct TextureFunction;
		struct TransitionNode;
		struct Vertex;
		namespace {
			void;

			struct CubeTransition;
			struct FlipTransition; 
			struct RotateTransition;
		}
		namespace PerformanceHUD {
			void;

			struct CounterInfo;
			struct CounterType;
			struct DisplayMode;
			struct PeakMode;
		}
		namespace SW {
			void;

			struct Poly;
			struct Texture;
			namespace Blend {
				void;

				struct Add;
				struct Clear;
				struct Color;
				struct ColorBurn;
				struct ColorDodge;
				struct Copy;
				struct CopyLCD;
				struct Darken;
				struct DarkenSover;
				struct Datop;
				struct Dest;
				struct Difference;
				struct Din;
				struct Divide;
				struct Dout;
				struct Dover;
				struct Exclusion;
				struct HardLight;
				struct Hue;
				struct Lighten;
				struct LightenSover;
				struct LinearBurn;
				struct LinearDodge;
				struct LinearLight;
				struct Luminosity;
				struct Min;
				struct Mul;
				struct Multiply;
				struct Overlay;
				struct PinLight;
				struct PlusD;
				struct Satop;
				struct Saturation;
				struct Screen;
				struct Sin;
				struct SoftLight;
				struct Sout;
				struct Sover;
				struct SoverLCD;
				struct SoverLCDGray;
				struct SubD;
				struct SubS;
				struct Subtract;
				struct Xor;
			}
			namespace Format {
				void;

				struct A8;
				struct ARGB8_Host;
				struct ARGB8_Rev;
				struct Af;
				struct Ah;
				struct CbYCrY8;
				struct L8;
				struct LA8;
				struct LX8;
				struct Lf;
				struct Lh;
				struct RGB5_Host;
				struct RGB5_Rev;
				struct RGBA5;
				struct RGBA8;
				struct RGBAf;
				struct RGBAh;
				struct RGBX8;
				struct S8;
				struct XRGB8_Host;
				struct XRGB8_Rev;
				struct YCbYCr8;
			}
		}
		namespace Shape {
			void;

			struct FlatteningIterator;
			struct Lines;
		}
	}
	namespace Render {
		void;

		struct AlignmentProperty;
		struct Animation;
		struct AnimationEvaluator;
		struct Array;
		struct BackdropBuffer;
		struct BackdropGroup;
		struct BackdropLayer;
		struct BackdropState;
		struct BasicAnimation;
		struct BasicAnimation0;
		struct Behavior;
		struct CFObject;
		struct CachedHandle;
		struct Coder;
		struct CompressedImage;
		struct CompressedImageFormat;
		struct Context;
		struct Decoder;
		struct DistanceFieldLayer;
		struct DynamicsBehavior;
		struct DynamicsSolver;
		struct EmitterBehavior;
		struct EmitterCell;
		struct EmitterLayer;
		struct EmitterState;
		struct Encoder;
		struct Fence;				// by hand
		struct Filter;
		struct ForceField;
		struct Function;
		struct FunctionName;
		struct Gradient;
		struct GradientLayer;
		struct GroupAnimation;
		struct Handle;
		struct Image;
		struct ImageCacheEntry;
		struct ImageFilter;
		struct ImageProvider;
		struct ImageProviderKey;
		struct ImageProviderSubImage;
		struct ImageQueue;
		struct InterpolatedFunction;
		struct Interpolator;
		struct KeyValue;
		struct KeyValueArray;
		struct KeyframeAnimation;
		struct Layer;
		struct LayerBehaviorState;
		struct LayerGravity;
		struct LayerHost;
		struct LayerNode;
		struct LayerSubclass;
		struct LayerShmem;						// by hand @ 20160428, from CA::Layer::fetch_geometry
		struct Light;
		struct LineCap;
		struct LineJoin;
		struct MatchMoveAnimation;
		struct MeshEdge;
		struct MeshFace;
		struct MeshTransform;
		struct MeshVertex;
		struct Message;							// by hand @ 20160530, from CA::Render::Encoder::send_message
		struct NamedFunction;
		struct NotificationName;
		struct Object;
		struct Path;
		struct PathFillRule;
		struct Pattern;
		struct PixelBuffer;
		struct PropertyAnimation;
		struct Proxy;
		struct RenderBuffer;
		struct ReplicatorLayer;
		struct ShadowCache;
		struct ShapeLayer;
		struct ShmemBitmap;				// by hand @ 20160411
		struct Shmem;
		template<typename _T> struct ShmemPtr;		// by hand @ 20160428, from CA::Layer::fetch_geometry
		struct Spline;
		struct Spring;
		struct SpringAnimation;
		struct String;
		struct SubpixelMaskLayer;
		struct Surface;
		struct Texture;
		struct TileCache;
		struct TileCacheEntry;
		struct TiledTexture;
		struct Timing;
		struct Transition;
		struct TransitionAnimation;
		struct Type;
		struct Update;
		struct Vector;
		struct occlusion_closure;
		struct occlusion_data;
		namespace EmitterBehaviors {
			void;

			struct AlignToMotion;
			struct Attractor;
			struct Drag;
			struct Light;
			struct NoOp;
			struct Wave;
		}
		namespace Server {
			void;

			struct CallbackBehavior;
			struct ReceivedMessage;
		}
		namespace Updater {
			void;

			struct FilterOp;
			struct FlattenZOp;
			struct GlobalState;
			struct LayerShapes;
			struct LayerShapesOp;
			struct LocalState;
			struct LocalState0;
			struct MeshOp;
			struct RasterizationOp;
			struct ShadowOp;
			struct TransformOp;
		}
	}
	namespace ScanConverter {
		void;

		struct FillRule;
		struct Path;
		namespace RendererImpl {
			void;

			struct Edge;
		}
	}
	namespace WindowServer {
		void;

		struct Display;
		struct MemorySurface;
		struct PurpleDisplay;
		struct Server;
		struct Surface;
		namespace {
			void;

		}
	}
}
namespace CAML {
	void;

	struct Context;
	struct ObjCBool;
	struct ObjCCAColorMatrix;
	struct ObjCCAPoint3D;
	struct ObjCCATransform3D;
	struct ObjCCGAffineTransform;
	struct ObjCCGColor;
	struct ObjCCGFont;
	struct ObjCCGImage;
	struct ObjCCGPDFDocument;
	struct ObjCCGPath;
	struct ObjCCGPoint;
	struct ObjCCGRect;
	struct ObjCCGSize;
	struct ObjCContext;
	struct ObjCInteger;
	struct ObjCNSArray;
	struct ObjCNSDictionary;
	struct ObjCNSObject;
	struct ObjCNSSet;
	struct ObjCNSURL;
	struct ObjCNull;
	struct ObjCReal;
	struct ObjCScript;
	struct ObjCString;
	struct ObjCType;
	struct State;
	struct StateName;
	struct Type;
}

struct CA::Context::Command;
struct CA::Context::Generic;
struct CA::Layer::Animation;
struct CA::Layer::CollectAnimationsData;
struct CA::Layer::CollectLayersData;
struct CA::OGL::Context::CacheItem;
struct CA::OGL::Context::DownsampleFilter;
struct CA::OGL::Context::SurfaceVolatility;
struct CA::OGL::ImagingNode::RenderClosure;
struct CA::OGL::SW::Poly::Vertex;
struct CA::Render::BackdropGroup::Item;
struct CA::Render::Coder::Attachment;
struct CA::Render::Context::ResourceTable;
struct CA::Render::DynamicsSolver::SpringLayer;
struct CA::Render::EmitterState::Cell;
struct CA::Render::EmitterState::Cells;
struct CA::Render::EmitterState::Particle;
struct CA::Render::Encoder::ObjectCache;
struct CA::Render::Handle::Dependence;
struct CA::Render::Image::SubimageKey;
struct CA::Render::Image::TiledImage;
struct CA::Render::Image::TiledImage::Key;
struct CA::Render::Image::TiledImage::Key;
struct CA::Render::Layer::Ext;
struct CA::Render::MatchMoveAnimation::Dependence;
struct CA::Render::ShadowCache::Entry;
struct CA::Render::Update::Backdrop;
struct CA::Transaction::Command;
struct CA::Transaction::Continuation;
struct CA::Transaction::Fence;
struct CA::Transaction::Join;
struct CA::Transaction::Level;
struct CA::WindowServer::Display::ColorMode;
struct CA::WindowServer::Display::Mode;
struct CA::WindowServer::Display::Orientation;
struct CA::WindowServer::Display::OverscanAdjustment;
struct CA::WindowServer::Display::SignalType;
struct CA::WindowServer::PurpleDisplay::Message;
struct CA::WindowServer::Server::PendingOrderAbove;
struct CA::WindowServer::Server::PendingOrderLevel;
struct CAML::Context::Object;


#endif // _CA_namespace__H_