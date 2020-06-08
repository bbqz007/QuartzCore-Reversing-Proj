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
#include "typedefs.h"
#include "OSAtomic.h"
#include "CA.struct.h"
enum _CAValueType {};

namespace CA
{
	void* callbacks;
	pthread_mutex_t callback_lock;
	__CFRunLoopTimer* callback_timer;
	x_list* active_timers;
}

namespace CA
{
	struct AttrList;
};
// by hand
struct CA::AttrList
{
	void set(unsigned int, _CAValueType, void const*);
	bool get(unsigned int, _CAValueType, void*);
	
};

struct CA::Bounds
{
	contains(CA::Shape const*) const;
	intersect_interior(CA::Shape const*);
	set_exterior(CA::Rect const&);
	set_interior(CA::Rect const&);
	set_rounded(CA::Rect const&);
	subtract_exterior(CA::Shape const*);

};
struct CA::ColorMatrix
{
	has_bias() const;
	is_alpha_identity() const;
	is_diagonal() const;
	is_identity() const;
	multiply_color(float, float, float, float);
	set_brightness(float);
	set_color(float const*);
	set_color_invert();
	set_color_monochrome(float, float, float const*);
	set_contrast(float);
	set_hue_rotate(float);
	set_identity();
	set_luminance_to_alpha();
	set_saturate(float);

};
struct CA::Context
{
	static OSSpinLock _lock;	// from CA::Context::Context @ 20160503
	static CA::Context* _contexts;		// head, from CA::Context::Context @ 20160503
	static int _last_local_id;	// from CA::Context::Context @ 20160503
	static mach_port _user_client_port;	// from CA::Context::connect_remote @ 20160504

	int _0;						// _refcnt, from CA::Context::Context @ 20160503
	CA::Context* _8;			// next, from CA::Context::Context @ 20160503
	_pthread_mutex _10;			// inline mutext, from CA::Context::commit_transaction @ 20160428
	X::Weak<void const*> _50;	// from CA::Context::Context @ 20160503
	int _58;					// from CA::Context::Context @ 20160503
	int _5c;					// id, from CA::Context::Context @ 20160503
	CALayer* _68;				// from CA::Context::commit_transaction @ 20160428
	CA::Render::Context* _70;	// from CA::Context::commit_transaction @ 20160428 
	CGColorSpace* _78;			// from CA::Context::Context @ 20160503
	__CFDictionary* _80;		// from CA::Context::destroy @ 20160503
	int32_t _90;				// some flag? from CA::Context::commit_transaction @ 20160428 
	CA::Render::Encoder::ObjectCache* _98;	// some flag? from CA::Context::commit_transaction @ 20160428 
	dispatch_source_t _a0;		// from CA::Context::destroy @ 20160503
	mach_port _a8;				// client port, from CA::Context::retain_context_with_client_port @ 20160503
	CA::GenericContext _b8;		// inline context, from CA::Layer::display_ @ 20160428
	CA::Context* _c0;
	int _c8;
	struct Command;
	struct Generic;
	Context(__CFDictionary const*);
	mach_port client_port();
	static void commit_animation(CA::Layer*, CA::Render::Animation*, void*);
	static void commit_command(Command, unsigned long, void const*);
	commit_command(int, unsigned long, void const*, void*);
	static void commit_deleted(unsigned long, unsigned int, void*);
	static void commit_layer(CA::Layer*, unsigned int, unsigned int, void*);
	static double commit_layer_time(CA::Layer*, double, void*);
	static void commit_root(CA::Layer*, void*);
	commit_transaction(CA::Transaction*);
	bool connect_local();
	bool connect_remote();
	mach_port create_fence_port();
	current_colorspace();
	static CGColorSpace* current_colorspace(CA::Transaction*);
	void delete_slot(unsigned int);
	void destroy();
	bool get_backdrop_layer_statistics(unsigned long, double*);
	bool get_layer_renderer_info(unsigned long, unsigned int, _CARenderRendererInfo*, unsigned long);
	void get_layer_shmem(unsigned long, CA::Render::ShmemPtr<CA::Render::LayerShmem>&);
	void invalidate();
	void invalidate_fences();
	bool is_secure();
	int32_t new_image_slot(unsigned int, unsigned int, bool);
	int32_t new_slot();
	remove_animation(CA::Layer*, __CFString const*, void*);
	static Context** retain_all_contexts(bool, CA::Context**, unsigned long&);
	static Context* retain_context_with_client_port(unsigned int);
	static Context* retain_context_with_id(unsigned int);
	CALayer* retain_layer() const;
	__CFArray* retain_objc_contexts();
	CA::Render::Context* retain_render_ctx();
	void set_colorspace(CGColorSpace*);
	set_layer(void const*);
	set_level(float);
	void set_objc_context(void const*);
	set_secure(bool);
	set_slot(unsigned int, void const*);
	bool synchronize(unsigned int, int);
	synchronize_transactions();
	unref(bool);
	~Context();

};
struct CA::Context::Command
{
	int32_t _0;
	uintptr_t _8;
};
struct CA::Context::Generic
{
	client_id();
	client_port();
	commit_seed();
	encoder_cache();
	layer_context();
	local_id();
	release();
	retain_render_context();
	server_port();
	synchronize(unsigned int, int);
	~Generic();

};
struct CA::DispatchGroup
{
	DispatchGroup(void(*)(void*, void*), void* const*, unsigned long, void*);
	callback_0(void*);
	callback_1(void*);
	dispatch(bool);
	enqueue(void(*)(void*), void*);
	init();
	~DispatchGroup();

};
struct CA::Display::Display
{
	new_display_link(__CFRunLoop*, X::List<__CFString const*> const*);
	safe_bounds() const;
	set_allows_virtual_modes(bool);
	set_color_mode(CA::WindowServer::Display::ColorMode);
	set_current_mode(CA::WindowServer::Display::Mode);
	set_overscan_adjustment(CA::WindowServer::Display::OverscanAdjustment);
	update();
	~Display();

};
struct CA::Display::DisplayLink
{
	DisplayLink(CA::Display::Display*, __CFRunLoop*, X::List<__CFString const*> const*);
	add_item(CA::Display::DisplayLinkItem*);
	add_timer(__CFRunLoopTimer*);
	dispatch_items(unsigned long long, unsigned long long, unsigned long long);
	display_refresh_rate_changed(CA::Display::Display*);
	get_link(CA::Display::Display*, __CFRunLoop*, X::List<__CFString const*> const*);
	remove_item(CA::Display::DisplayLinkItem*);
	unref();
	update_paused();
	update_paused_locked();
	update_timer();
	~DisplayLink();

};
struct CA::Display::DisplayLinkItem
{
	DisplayLinkItem(CA::Display::Display*, void const*, objc_selector*);
	dispatch();
	invalidate();
	schedule(__CFRunLoop*, __CFString const*);
	set_paused(bool);
	set_user_info(void const*);
	unschedule(__CFRunLoop*, __CFString const*);
	update_link(__CFRunLoop*);
	~DisplayLinkItem();

};
struct CA::Display::EmulatorDisplay
{
	~EmulatorDisplay();

};
struct CA::Display::TimerDisplayLink
{
	TimerDisplayLink(CA::Display::Display*, __CFRunLoop*, X::List<__CFString const*> const*);
	add_to_mode(__CFString const*);
	callback(__CFRunLoopTimer*, void*);
	pause_timer();
	remove_from_mode(__CFString const*);
	start_timer();
	update_timer();
	~TimerDisplayLink();

};
struct CA::GenericContext
{
	cpp_virtbl* _0;
	committing_context();
	retain_context_with_id(unsigned int);

};

struct CALayer;
struct CA::Layer
{
	struct Animation;
	struct CollectAnimationsData;
	struct CollectLayersData;
	struct State
	{
		unsigned int _0;		// from class_state
		unsigned int _4;			// some flags, from CA::Layer::set_commit_needed, this->_2c, offset 4 to &this->_28;
		CA::Vec2<double> _8;
		double _18;				// x, from CA::Layer::set_bounds @ 20160416
		double _20;				// y, from CA::Layer::set_bounds @ 20160416
		double _28;				// width, from CA::Layer::set_bounds @ 20160416
		double _30;				// height, from CA::Layer::set_bounds @ 20160416
		unsigned int _3c;
		void* _40;				// from class_state @ 20160422
		void* _48;				// from class_state @ 20160422
		CA::AttrList* _50;		// from class_state @ 20160422
		unsigned int _58;
		unsigned int _5c;		// some flags, from CA::Layer::set_bounds @ 20160416
		unsigned int _60;		// some flags
		unsigned int _64;
		State* _68;				// from CA::Layer::Layer @ 20160501
		Animation* _70;
		unsigned int _88;		// some flags, from CA::Layer::display @ 20160428
		set_delegate(CA::Transaction*, objc_object*);
		static void unref(CA::Transaction*);
	};
	uint32_t _0;
	uint32_t _4;
	CA::Layer* _8;	// sublayer, from update_added_sublayer @ 20160516. next? there is doubt @ 20160416 review, from set_needs_layout @ ?
	CALayer* _10;	// superlayer, from superlayer @ 20160516. ? read-only layer , from CA::Layer::begin_change @ 20160419
	__CFArray* _18;	// sublayers
	CALayer* _20;	// mask? from set_sublayers.    i guess it may be superlayer. but it can be maskLayer, from set_mask
	State& _28;		// state, from set_delegate @20160415, inline state
	CA::Vec2<double> _30;			// from fetch_geometry @20150428
	double _40;		// x
	double _48;		// y
	double _50;		// width, from display_ @20160410
	double _58;		// height, from display_ @20160410
	objc_object* _60;		// delegate, from set_delegate @20160415
	void* _68;				// from decl of State::_40
	void* _70;				// from decl of State::_48
	CA::AttrList* _78;		// from fetch_geometry @20160429
	int32_t _80;
	int32_t _84;
	int32_t _88;
	int32_t _8c;
	State* _90;	// from free_transaction @ 20160429(CA::Transaction*), fixup @ 20160501, 
	Animation* _98;
	int32_t _a0;			// a value return from CA::Render::next_sequence(), from CA::Layer::commit_if_needed
	int32_t _a4;			// visibleFlags, from set_visible @ 20160516. insead that, id which is the arguement of CA::Context::retain_context_with_id, from CA::Layer::retain_context, also xref by inerst_sublayer
	int32_t _a8[0];
	CA::Render::ShmemPtr<CA::Render::LayerShmem>*& _b8;			// _a8[(0xb8-0xa8)>>2], from fetch_geometry @20160429
	Layer(CALayer*, State const&, State const*, CA::Transaction*, unsigned int);
	void add_animation(CAAnimation*, __CFString const*);
	uintptr_t animation_heart_beat(double, void*);
	void animation_visibility_changed(CA::Transaction*, bool);
	void begin_change(CA::Transaction*, unsigned int, objc_object*&);
	void call_did_become_visible();
	static int changed_flags_for_class(objc_class*);
	State* class_state(objc_class*);
	collect_animations(CA::Transaction*, double, double*);
	collect_animations_(double, double*, CollectAnimationsData*);
	bool collect_animations__(double, double*, CollectAnimationsData*);
	void collect_layers_(CollectLayersData*);
	static void collect_non_visible_animations(CA::Transaction*);
	static void collect_non_visible_callback(void const*, void*);
	void commit_animations(CA::Transaction*, double(*)(CA::Layer*, double, void*), void(*)(CA::Layer*, CA::Render::Animation*, void*), void(*)(CA::Layer*, __CFString const*, void*), void*);
	void commit_if_needed(CA::Transaction*, void(*)(CA::Layer*, unsigned int, unsigned int, void*), void*);
	void commit_thread_flags(unsigned int);
	void contents_visibility_changed(CA::Transaction*, bool);
	static bool convert_time(CA::Transaction*, double&, CALayer*, CALayer*);
	CA::Render::Layer* copy_render_layer(CA::Transaction*, unsigned int, unsigned int*);
	void default_value(unsigned int, _CAValueType, void*);
	void did_commit(CA::Transaction*);
	void display();
	void display_();
	bool sdisplay_if_needed(CA::Transaction*);
	void end_change(CA::Transaction*, unsigned int, objc_object*);
	void ensure_mipmaps();
	void ensure_transaction_recursively(CA::Transaction*);
	void* fetch_defaults();
	void fetch_geometry(CA::Transaction*);
	static void free_animation(Animation*, bool);
	void free_transaction(CA::Transaction*);
	void get_frame_transform(CA::Mat4<double>&, bool, CA::Mat4<double> const*);
	void get_frame_transform(CGAffineTransform&, bool);
	void getter(unsigned int, _CAValueType, void*);
	void insert_sublayer(CA::Transaction*, CALayer*, unsigned long);
	void invalidate_animations(CA::Transaction*);
	void invalidate_contents();
	void invalidate_layout();
	void invalidate_sublayers(CA::Transaction*);
	bool is_visible() const;
	void latch_thread_flags(CA::Transaction*, unsigned int*);
	CALayer* layer_at_time(CA::Transaction*, double, bool, bool);
	CALayer* layer_being_drawn(CA::Transaction*, unsigned int);
	void layout_and_display_if_needed(CA::Transaction*);
	void layout_if_needed(CA::Transaction*);
	bool layout_is_active(CA::Transaction*, bool);
	static void map_geometry(CALayer*, CALayer*, void(*)(void*, CA::Mat4<double> const&), void(*)(void*, CA::Mat4<double> const&), void*);
	void mark(CA::Transaction*, unsigned int, unsigned int);
	void mark_animations(CA::Transaction*, bool);
	void mark_context_changed(CA::Transaction*);
	void mark_sublayers_should_fetch_geometry();
	void mark_visible(CA::Transaction*, bool);
	CALayer* mask();
	CA::Layer* model_layer(CA::Transaction*);
	bool needs_display();
	bool needs_layout();
	void prepare_animations(CA::Transaction*);
	void prepare_commit(CA::Transaction*);
	void prepare_context_for_drawing(CGContext*, bool, bool);
	CALayer* presentation_layer(CA::Transaction*);
	void property_did_change(CA::Transaction*, unsigned int);
	void remove_from_context();
	void remove_from_superlayer();
	void remove_sublayer(CA::Transaction*, CALayer*);
	X::Ref<CA::Render::Timing> render_timing(CA::Transaction*);
	void replace_sublayer(CA::Transaction*, CALayer*, CALayer*);
	CA::Context* retain_context();
	void run_animation_callbacks(void*);
	void run_animation_callbacks_compat(double, void*);
	void set_animations(Animation*);
	void set_bit(unsigned int, unsigned int, unsigned int, bool, void(CA::Layer::*)(CA::Transaction*));
	void set_bit_int(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	void set_bounds(CA::Rect const&, bool);
	void set_commit_needed(CA::Transaction*, unsigned int);
	void set_delegate(objc_object*);
	void set_mask(CALayer*);
	void set_model_layer(CA::Transaction*, CA::Layer*);
	void set_needs_display_in_rect(CGRect const&);
	void set_needs_layout();
	void set_next_animation_time(CA::Transaction*, double, double);
	void set_position(CA::Vec2<double> const&, bool);
	void set_sublayers(__CFArray const*);
	void set_visible(unsigned int);
	void setter(unsigned int, _CAValueType, void const*);
	bool style_value(unsigned int, objc_object**);
	CALayerArray* sublayers();
	CALayer* superlayer();
	uint32_t* thread_flags_(CA::Transaction*);
	void toggle_flipped(CA::Transaction*);
	void update_added_sublayer(CA::Transaction*, CA::Layer*, unsigned int);
	void update_for_changed_sublayers(CA::Transaction*, unsigned int);
	void update_removed_sublayer(CA::Transaction*, unsigned int);
	void update_sublayers(CA::Transaction*, CALayerArray*, CALayerArray*);
	State* writable_state(CA::Transaction*);
	~Layer();

}; 
struct CAAnimation;
struct CA::Layer::Animation
{
	Animation* _0;					// ? next
	CAAnimation* _8;
	void* _10;
	__CFString* _18;				// key_path
	CA::Render::Timing* _20;
	int _28;						// flag? from commit_animations @ 20160425, assigned to CA::Render::Animation::_30
	int _2c;						// flag? from commit_animations @ 20160425
	CA::Transaction::Continuation* _30;			// continuation, from add_animation @ 20160512
	short _38;
};
struct CA::Layer::CollectAnimationsData
{
	float _8;
	uint32_t _c;
};
struct CA::Layer::CollectLayersData
{
	void* _0;			// slist { CA::Layer*; slist*; }, from layout_if_needed @ 20160417
	void* _8;							// slist { CA::Layer*; slist*; }, fromCA::Layer::layout_if_needed @ 20160422
	int64_t _10;					// count of slist, from CA::Layer::collect_layers_ @ 20160422
	CA::Transaction* _18;			// from CA::Layer::collect_layers_ @ 20160422
	struct {
		struct slist {
			CA::Layer* _0;			// val
			slist* _8;				// next
		} * _8;						// free buffers, point to slist[count]
		int64_t	_10;				// count * sizeof(slist);
	}*_20;			// from CA::Layer::collect_layers_ @ 20160422
	unsigned int _28;
	unsigned int _2c;
	unsigned int _30;
};
struct CA::OGL::(anonymous namespace)::RenderSurface
{

};
struct CA::OGL::BackdropBuffer
{
	get_size(unsigned int&, unsigned int&, float&);
	~BackdropBuffer();

};
struct CA::OGL::BackdropNode
{
	compute_dod(CA::Bounds&);
	retain_surface(float&, unsigned int);
	~BackdropNode();

};
struct CA::OGL::BlendFunction
{

};
struct CA::OGL::BlendNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	propagate_roi(CA::Bounds const&);
	~BlendNode();

};
struct CA::OGL::CacheNode
{
	CacheNode(CA::OGL::Renderer&, CA::OGL::Layer*, CA::OGL::ImagingNode*, CA::Render::CacheId const&, bool);
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	grow_roi(CA::Bounds&);
	propagate_roi(CA::Bounds const&);
	retain_surface(float&, unsigned int);
	~CacheNode();

};
struct CA::OGL::Color
{
	apply_light(CA::Vec3<float> const&);
	lerp(CA::OGL::Color const&, unsigned int);
	multiply(CA::OGL::Color const&);
	scale(unsigned int);

};
struct CA::OGL::CombineNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	propagate_roi(CA::Bounds const&);
	~CombineNode();

};
struct CA::OGL::CompositeNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	needs_surface(bool) const;
	propagate_roi(CA::Bounds const&);
	~CompositeNode();

};
struct CA::OGL::ContentsGeometry
{
	ContentsGeometry(CA::OGL::Layer const&, CA::OGL::Gstate const&, CA::Render::Texture*, CA::OGL::Context*);
	fill_and_unbind(CA::OGL::Context&, CA::OGL::Image*) const;
	fill_and_unbind(CA::OGL::Context&, CA::OGL::Image*, CA::OGL::TextureFilter, float) const;
	fill_debug(CA::OGL::Context&, CA::Render::Texture*, bool, CA::OGL::ImageFunction) const;
	scale() const;

};
struct CA::OGL::Context
{
	struct CacheItem;
	struct DownsampleFilter;
	struct SurfaceVolatility;
	Context();
	array_color(unsigned int);
	array_color1(unsigned int);
	array_color_vec(unsigned int*);
	array_flush();
	array_indices(unsigned int);
	array_indices_vec(unsigned short const*);
	array_quad(CA::Vec2<double> const&, CA::Vec2<double> const&, CA::Vec2<double> const&, CA::Vec2<double> const&);
	array_quad(CA::Vec2<float> const&, CA::Vec2<float> const&, CA::Vec2<float> const&, CA::Vec2<float> const&);
	array_quad(CA::Vec4<double> const&, CA::Vec4<double> const&, CA::Vec4<double> const&, CA::Vec4<double> const&);
	array_quad(CA::Vec4<float> const&, CA::Vec4<float> const&, CA::Vec4<float> const&, CA::Vec4<float> const&);
	array_quad_normals(CA::Vec3<float> const&, CA::Vec3<float> const&, CA::Vec3<float> const&, CA::Vec3<float> const&);
	array_rect(float, float, float, float);
	array_tex_quad(unsigned int, CA::Vec2<float> const&, CA::Vec2<float> const&, CA::Vec2<float> const&, CA::Vec2<float> const&);
	array_tex_rect(unsigned int, float, float, float, float);
	assembly_buffer_bounds() const;
	attached_to_framebuffer_p() const;
	begin_rendering(CA::OGL::Gstate const*);
	bind_circle(unsigned int, int, bool, float*);
	bind_image(unsigned int, CA::Render::Texture*, unsigned int, CA::OGL::TextureFilter, CA::OGL::TextureFilter, float, CA::OGL::TextureEdgeMode, CA::OGL::ContentsGeometry const*, float*, char const*);
	bind_square(unsigned int, CA::Transform const&, bool, float*);
	bind_surface(CA::OGL::Surface*, int, unsigned int, CA::OGL::TextureFilter, CA::OGL::TextureFilter, float);
	blur_surface(float, CA::OGL::Surface*, float, BlurParams const&, CA::Shape const*);
	cache_fetch(CA::Render::CacheId const&);
	cache_get_roi(CacheItem*, CA::Bounds&);
	cache_get_surface(CacheItem*, CA::Bounds const&);
	cache_set_surface(CacheItem*, CA::OGL::Surface*);
	can_tile_image(CA::Render::Texture*, unsigned int, unsigned int);
	chroma_location(unsigned int, CA::OGL::Image*, CA::Render::Texture*, bool);
	clear_context();
	clear_readback_surface_list();
	collect(bool);
	copy_destination(int, CA::OGL::Surface*, unsigned long, CA::Bounds const*, int const*, bool&);
	create_mutable_image(unsigned int, unsigned int, unsigned int, CGColorSpace*);
	create_reinterpreted_surface(CA::OGL::Surface*, bool);
	destination_has_alpha_p() const;
	downsample_surface(CA::OGL::Surface*, CA::Vec2<double> const&, CA::Transform const&, DownsampleFilter, float);
	draw_elements(CA::OGL::PrimitiveMode, unsigned int, unsigned short const*, CA::OGL::Vertex const*, unsigned int, unsigned int, CA::OGL::ClipPlane const*);
	draw_lines(unsigned int, unsigned int, CA::OGL::LineVertex const*);
	dynamic_cast_gl_context();
	edge_mode_supported(CA::Render::Texture*, CA::OGL::TextureEdgeMode);
	end_rendering(CA::OGL::Gstate const*);
	extend_surface(CA::OGL::Surface*, int);
	finish();
	finish_image(CA::OGL::Image*, bool);
	flatten_detached_layers_();
	flush(bool);
	get(CA::OGL::ContextProperty);
	get_clip_bounds(CA::Bounds&) const;
	image_deleted(CA::Render::Object*, void*, void*);
	image_surface(CA::OGL::Image*, CA::Render::Texture*);
	image_volatile(CA::Render::Object*, void*, void*);
	init_state();
	initialize_perf_hud();
	insert_event_marker(char const*);
	invalidate_backend_ctx();
	invalidate_destination();
	lookup_image_(CA::Render::Texture*, bool);
	make_buffer_current(CA::WindowServer::Surface*);
	marked_destination();
	marked_surface(CA::OGL::Surface*);
	modify_subimage_impl(CA::OGL::Image*, CA::Render::Texture*, unsigned int, int, int, int, int, void const*, unsigned int);
	need_blending(bool);
	need_transparent_source();
	needs_destination_group();
	new_image();
	pop_group_marker();
	pop_surface();
	prepare_context(CA::OGL::ContextState*);
	prepare_destination_();
	purge(bool);
	push_context_state(CA::OGL::ContextState*);
	push_group_marker(char const*);
	push_surface(CA::OGL::Surface*, bool, unsigned int);
	read_destination();
	read_surface(CA::OGL::Surface*, int);
	readback_surface() const;
	release_surface(CA::OGL::Surface*);
	release_surface_async(CA::OGL::Surface*);
	remove_images(CA::Render::Object const*, CA::OGL::Image*, void*);
	reset_statistics();
	restore_context_state(CA::OGL::ContextState*);
	restore_state();
	retain_null_surface();
	reuse_surface(CA::OGL::Surface*, CA::Bounds);
	set_accelerator(unsigned int);
	set_backend_ctx(void*);
	set_colorspace(CGColorSpace*);
	set_dest_transforms(CA::Transform const* const*);
	set_destination(void*, long, unsigned long, void*, long, int, int, int, int);
	set_destination_texture(unsigned long, unsigned long, bool);
	set_feature_flags(unsigned int);
	set_gstate(CA::OGL::Gstate const*);
	set_motion_transform(CA::Transform const*);
	set_surface_volatile(CA::OGL::Surface*, SurfaceVolatility);
	shadow_cache();
	should_tile_image(CA::Render::Texture*);
	state_requires_disjoint_primitives();
	subimage_max_rowbytes(unsigned int, unsigned int, unsigned int);
	sw_renderer_p();
	targets_assembly_buffer() const;
	texture_function_image();
	tile_cache();
	tile_cache_load(CA::OGL::ContentsGeometry&, CA::Render::Texture*, CA::OGL::TextureFilter&);
	unbind_image(CA::OGL::Image*, unsigned int);
	unbind_surface(CA::OGL::Surface*, int, unsigned int);
	update();
	update_debug_message(CA::Transform const*, CA::Shape const*);
	update_perf_hud(CA::Transform const*, CA::Shape const*);
	update_time() const;
	warmup_shaders();
	~Context();

};
struct CA::OGL::Context::CacheItem
{

};
struct CA::OGL::Context::DownsampleFilter
{

};
struct CA::OGL::Context::SurfaceVolatility
{

};
struct CA::OGL::ContextProperty
{

};
struct CA::OGL::ContextState
{

};
struct CA::OGL::DebugRenderer
{
	DebugRenderer(CA::OGL::Context&, unsigned long);
	apply_display_rotation(CA::Transform&);
	begin();
	capture_background(CA::Transform const&, CA::Shape const*);
	clear();
	draw_bar(float);
	draw_rectangle_with_fill(CA::Vec2<float> const&);
	draw_string(char const*, unsigned long);
	end();
	render(CA::Transform const*, CA::Shape const*);
	render_background();
	~DebugRenderer();

};
struct CA::OGL::Filter
{

};
struct CA::OGL::FilterNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	needs_surface(bool) const;
	propagate_roi(CA::Bounds const&);
	~FilterNode();

};
struct CA::OGL::GLContext
{
	GLContext(void*);
	array_init();
	assemble_fragment_shader(CA::OGL::GLShader const*, int*);
	assemble_vertex_shader(CA::OGL::GLShader const*);
	bind_noise(unsigned int);
	check_extension(char const*, char const*, char const*);
	clear_region(CA::Shape const*, unsigned int);
	collect(bool);
	create_shader(CA::OGL::ContextState const*, CA::OGL::GLShader const*, int);
	delete_destination_texture();
	destination_texture_target();
	disable_client_state();
	draw_elements(CA::OGL::PrimitiveMode, unsigned int, unsigned short const*, CA::OGL::Vertex const*, unsigned int, unsigned int);
	draw_elements(CA::OGL::PrimitiveMode, unsigned int, unsigned short const*, CA::OGL::Vertex const*, unsigned int, unsigned int, CA::OGL::ClipPlane const*);
	draw_lines(unsigned int, unsigned int, CA::OGL::LineVertex const*);
	draw_triangles(CA::OGL::Vertex*, unsigned int, void*);
	dynamic_cast_gl_context();
	ensure_destination_texture(CA::Bounds const&);
	finish();
	flush(bool);
	function_supported();
	function_uniform(unsigned int, unsigned long, unsigned long, float const*);
	get(CA::OGL::ContextProperty);
	get_shader(CA::OGL::ContextState const*);
	init_client_state(CA::OGL::Vertex const*);
	init_client_state_lines(CA::OGL::LineVertex const*);
	init_state();
	inline_blend_function(x_stream_struct*, CA::OGL::BlendFunction, int);
	insert_event_marker(char const*);
	load_blend_func(CA::OGL::BlendFunction, CA::OGL::BlendFunction);
	needs_destination_group();
	pop_group_marker();
	projection_matrix();
	projection_matrix(float, float, float, float, bool);
	purge(bool);
	purge_shaders();
	push_group_marker(char const*);
	restore_state();
	shader_preamble();
	state_requires_disjoint_primitives();
	unload_state();
	update_shader();
	update_state();
	update_texture(unsigned int);
	viewport();
	viewport(int, int, int, int, bool);
	window_bounds(CA::Bounds&);
	~GLContext();

};
struct CA::OGL::GLESContext
{
	GLESContext(void*);
	attached_to_framebuffer_p() const;
	bind_circle(unsigned int, int, bool, float*);
	bind_destination_with_filters(unsigned int, CA::OGL::TextureFilter, CA::OGL::TextureFilter);
	bind_gaussian(unsigned int, float*);
	bind_image_impl(unsigned int, CA::Render::Texture*, unsigned int, CA::OGL::TextureFilter, CA::OGL::TextureFilter, float, CA::OGL::TextureEdgeMode, float*, char const*);
	bind_noise(unsigned int);
	bind_square(unsigned int, CA::Transform const&, bool, float*);
	bind_surface_impl(CA::OGL::Surface*, int, unsigned int, CA::OGL::TextureFilter, CA::OGL::TextureFilter, float);
	copy_destination(int, CA::OGL::Surface*, unsigned long, CA::Bounds const*, int const*, bool&);
	create_mutable_image(unsigned int, unsigned int, unsigned int, CGColorSpace*);
	create_null_surface();
	create_surface(int, CA::Bounds const&, unsigned int);
	create_surface_from_data(void*, long, int, int, int, int, bool);
	delete_image(CA::OGL::Image*);
	destination_has_alpha_p() const;
	destination_texture_target();
	edge_mode_supported(CA::Render::Texture*, CA::OGL::TextureEdgeMode);
	ensure_destination_texture(CA::Bounds const&);
	finalize_surface(CA::OGL::Surface*);
	finish();
	finish_image(CA::OGL::Image*, bool);
	flush_texture_cache(unsigned int);
	get(CA::OGL::ContextProperty);
	image_data_tightly_packed_p(CA::Render::Image const*);
	image_parameters(unsigned int, int, unsigned int&, unsigned int&, unsigned int&, CA::OGL::ImageFunction&, bool&);
	image_surface(CA::OGL::Image*, CA::Render::Texture*);
	init_state();
	make_buffer_current(CA::WindowServer::Surface*);
	mipmapped_texture(unsigned int, unsigned long, unsigned long, unsigned char const*);
	modify_subimage_impl(CA::OGL::Image*, CA::Render::Texture*, unsigned int, int, int, int, int, void const*, unsigned int);
	new_image();
	purge(bool);
	release_display_surface(CA::WindowServer::Surface*, void*);
	retain_image(CA::OGL::Image*, CA::Render::Texture*, bool);
	set_destination_texture(unsigned long, unsigned long, bool);
	set_surface(CA::OGL::Surface*);
	shader_preamble();
	should_tile_image(CA::Render::Texture*);
	subimage_max_rowbytes(unsigned int, unsigned int, unsigned int);
	supports_api_version(unsigned int);
	surface_texture_target(CA::OGL::Surface*);
	update();
	update_image(CA::OGL::GLESImage*, CA::Render::Image*, unsigned int);
	update_limits();
	update_texture_plane(CA::OGL::GLESImage*, unsigned int, int);
	warmup_shaders();
	window_bounds(CA::Bounds&);
	~GLESContext();

};
struct CA::OGL::GLESImage
{
	~GLESImage();

};
struct CA::OGL::GLShader
{

};
struct CA::OGL::Gstate
{

};
struct CA::OGL::Image
{
	~Image();

};
struct CA::OGL::ImageFunction
{

};
struct CA::OGL::ImagingNode
{
	struct RenderClosure;
	ImagingNode(CA::OGL::Renderer&, CA::OGL::Layer*, CA::OGL::ImagingNode*, CA::OGL::ImagingNode*, CA::OGL::ImagingNode*);
	add_roi(CA::Bounds const&);
	apply(float, CA::OGL::Surface**, float*);
	finalize(CA::OGL::Renderer&);
	grow_roi(CA::Bounds&);
	init_roi(unsigned int);
	layer_node_p() const;
	needs_surface(bool) const;
	operator delete(void*);
	operator new(unsigned long, CA::OGL::Renderer&);
	propagate_roi(CA::Bounds const&);
	render(RenderClosure*, unsigned int);
	retain_surface(float&, unsigned int);
	set_roi(CA::Bounds const&);
	set_roi(CA::Shape const*);
	~ImagingNode();

};
struct CA::OGL::ImagingNode::RenderClosure
{

};
struct CA::OGL::Layer
{

};
struct CA::OGL::LayerNode
{
	add_roi(CA::Bounds const&);
	apply(float, CA::OGL::Surface**, float*);
	apply(float, CA::OGL::Surface**, float*)::visitor::visit_behavior(CA::Render::DynamicsBehavior*) const;
	compute_dod(CA::Bounds&);
	layer_node_p() const;
	retain_surface(float&, unsigned int);
	~LayerNode();

};
struct CA::OGL::MaskNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	needs_surface(bool) const;
	propagate_roi(CA::Bounds const&);
	~MaskNode();

};
struct CA::OGL::MeshNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	propagate_roi(CA::Bounds const&);
	~MeshNode();

};
struct CA::OGL::MotionBlurNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	propagate_roi(CA::Bounds const&);
	surface_buffers() const;
	~MotionBlurNode();

};
struct CA::OGL::PerformanceHUD::CounterInfo
{
	draw_value(CA::OGL::DebugRenderer&, CA::Vec2<float>) const;
	set_display_mode(CA::OGL::PerformanceHUD::DisplayMode);
	~CounterInfo();

};
struct CA::OGL::PerformanceHUD::CounterType
{

};
struct CA::OGL::PerformanceHUD::DisplayMode
{

};
struct CA::OGL::PerformanceHUD::PeakMode
{

};
struct CA::OGL::PingPongState
{
	bind_source(unsigned int, int*, bool);
	clear_edges(float, float, float, float, float);
	color_matrix(CA::ColorMatrix const&);
	create_surface(int, CA::Bounds const&);
	render_pass(int, int, float, float, bool, unsigned int, float, float);
	render_pass_final_dest(int, int, int, bool);
	replicate_edges(float, float, float, float, float, float, float, float, float);
	scale_and_dilate(float, float, int, int);
	~PingPongState();

};
struct CA::OGL::PrimitiveMode
{

};
struct CA::OGL::QuadNode
{
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	propagate_roi(CA::Bounds const&);
	~QuadNode();

};
struct CA::OGL::Renderer
{
	Renderer(CA::OGL::Context&);
	add_clip_plane(CA::OGL::Layer*);
	alloc_layer(CA::Render::LayerNode*, CA::OGL::Layer&, CA::OGL::Gstate const&);
	collect(CA::Render::Update const*, double);
	dealloc_layer(CA::OGL::Layer*);
	prepare_clip_shape(CA::Render::Update const*);
	purge(bool);
	render(CA::Render::Update const*);
	set_clip_shape(CA::Shape*);
	update_detached_layer(CA::Render::Handle*, long, CA::Render::Texture*, void*);
	~Renderer();

};
struct CA::OGL::SW::Blend::Add
{

};
struct CA::OGL::SW::Blend::Clear
{

};
struct CA::OGL::SW::Blend::Color
{

};
struct CA::OGL::SW::Blend::ColorBurn
{

};
struct CA::OGL::SW::Blend::ColorDodge
{

};
struct CA::OGL::SW::Blend::Copy
{

};
struct CA::OGL::SW::Blend::CopyLCD
{
	f(unsigned int&, unsigned int, unsigned int);

};
struct CA::OGL::SW::Blend::Darken
{

};
struct CA::OGL::SW::Blend::DarkenSover
{
	f(unsigned int&, unsigned int, unsigned int);

};
struct CA::OGL::SW::Blend::Datop
{

};
struct CA::OGL::SW::Blend::Dest
{

};
struct CA::OGL::SW::Blend::Difference
{

};
struct CA::OGL::SW::Blend::Din
{

};
struct CA::OGL::SW::Blend::Divide
{

};
struct CA::OGL::SW::Blend::Dout
{

};
struct CA::OGL::SW::Blend::Dover
{

};
struct CA::OGL::SW::Blend::Exclusion
{

};
struct CA::OGL::SW::Blend::HardLight
{

};
struct CA::OGL::SW::Blend::Hue
{

};
struct CA::OGL::SW::Blend::Lighten
{

};
struct CA::OGL::SW::Blend::LightenSover
{
	f(unsigned int&, unsigned int, unsigned int);

};
struct CA::OGL::SW::Blend::LinearBurn
{

};
struct CA::OGL::SW::Blend::LinearDodge
{

};
struct CA::OGL::SW::Blend::LinearLight
{

};
struct CA::OGL::SW::Blend::Luminosity
{

};
struct CA::OGL::SW::Blend::Min
{

};
struct CA::OGL::SW::Blend::Mul
{

};
struct CA::OGL::SW::Blend::Multiply
{

};
struct CA::OGL::SW::Blend::Overlay
{
	b(int&, int, int, int, int);

};
struct CA::OGL::SW::Blend::PinLight
{
	b(int&, int, int, int, int);

};
struct CA::OGL::SW::Blend::PlusD
{

};
struct CA::OGL::SW::Blend::Satop
{

};
struct CA::OGL::SW::Blend::Saturation
{

};
struct CA::OGL::SW::Blend::Screen
{

};
struct CA::OGL::SW::Blend::Sin
{

};
struct CA::OGL::SW::Blend::SoftLight
{

};
struct CA::OGL::SW::Blend::Sout
{

};
struct CA::OGL::SW::Blend::Sover
{

};
struct CA::OGL::SW::Blend::SoverLCD
{
	f(unsigned int&, unsigned int, unsigned int);

};
struct CA::OGL::SW::Blend::SoverLCDGray
{
	f(unsigned int&, unsigned int, unsigned int);

};
struct CA::OGL::SW::Blend::SubD
{

};
struct CA::OGL::SW::Blend::SubS
{

};
struct CA::OGL::SW::Blend::Subtract
{

};
struct CA::OGL::SW::Blend::Xor
{

};
struct CA::OGL::SW::Format::A8
{

};
struct CA::OGL::SW::Format::ARGB8_Host
{

};
struct CA::OGL::SW::Format::ARGB8_Rev
{

};
struct CA::OGL::SW::Format::Af
{

};
struct CA::OGL::SW::Format::Ah
{
	load_1(unsigned int&, unsigned char const*);

};
struct CA::OGL::SW::Format::CbYCrY8
{
	load_1(unsigned int&, unsigned char const*);

};
struct CA::OGL::SW::Format::L8
{

};
struct CA::OGL::SW::Format::LA8
{

};
struct CA::OGL::SW::Format::LX8
{

};
struct CA::OGL::SW::Format::Lf
{

};
struct CA::OGL::SW::Format::Lh
{
	load_1(unsigned int&, unsigned char const*);

};
struct CA::OGL::SW::Format::RGB5_Host
{

};
struct CA::OGL::SW::Format::RGB5_Rev
{

};
struct CA::OGL::SW::Format::RGBA5
{

};
struct CA::OGL::SW::Format::RGBA8
{

};
struct CA::OGL::SW::Format::RGBAf
{
	load_1(unsigned int&, unsigned char const*);

};
struct CA::OGL::SW::Format::RGBAh
{
	load_1(unsigned int&, unsigned char const*);

};
struct CA::OGL::SW::Format::RGBX8
{

};
struct CA::OGL::SW::Format::S8
{

};
struct CA::OGL::SW::Format::XRGB8_Host
{

};
struct CA::OGL::SW::Format::XRGB8_Rev
{

};
struct CA::OGL::SW::Format::YCbYCr8
{
	load_1(unsigned int&, unsigned char const*);

};
struct CA::OGL::SW::Poly
{
	struct Vertex;

};
struct CA::OGL::SW::Poly::Vertex
{

};
struct CA::OGL::SW::Texture
{

};
struct CA::OGL::SWContext
{
	array_init();
	bind_circle(unsigned int, int, bool, float*);
	bind_gaussian(unsigned int, float*);
	bind_image_impl(unsigned int, CA::Render::Texture*, unsigned int, CA::OGL::TextureFilter, CA::OGL::TextureFilter, float, CA::OGL::TextureEdgeMode, float*, char const*);
	bind_square(unsigned int, CA::Transform const&, bool, float*);
	bind_surface_impl(CA::OGL::Surface*, int, unsigned int, CA::OGL::TextureFilter, CA::OGL::TextureFilter, float);
	blur_surface(float, CA::OGL::Surface*, float, CA::OGL::Context::BlurParams const&, CA::Shape const*);
	clear_region(CA::Shape const*, unsigned int);
	copy_destination(int, CA::OGL::Surface*, unsigned long, CA::Bounds const*, int const*, bool&);
	create_null_surface();
	create_surface(int, CA::Bounds const&, unsigned int);
	create_surface_from_data(void*, long, int, int, int, int, bool);
	delete_image(CA::OGL::Image*);
	draw_elements(CA::OGL::PrimitiveMode, unsigned int, unsigned short const*, CA::OGL::Vertex const*, unsigned int, unsigned int);
	draw_elements(CA::OGL::PrimitiveMode, unsigned int, unsigned short const*, CA::OGL::Vertex const*, unsigned int, unsigned int, CA::OGL::ClipPlane const*);
	finalize_surface(CA::OGL::Surface*);
	function_supported();
	function_uniform(unsigned int, unsigned long, unsigned long, float const*);
	get(CA::OGL::ContextProperty);
	image_surface(CA::OGL::Image*, CA::Render::Texture*);
	make_buffer_current(CA::WindowServer::Surface*);
	needs_destination_group();
	new_image();
	retain_image(CA::OGL::Image*, CA::Render::Texture*);
	reuse_surface(CA::OGL::Surface*, CA::Bounds);
	set_destination(void*, long, unsigned long, void*, long, int, int, int, int);
	set_surface(CA::OGL::Surface*);
	sw_renderer_p();
	~SWContext();

};
struct CA::OGL::SWImage
{
	~SWImage();

};
struct CA::OGL::ShadowNode
{
	add_roi(CA::Bounds const&);
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	map_bounds(CA::Bounds&, bool);
	needs_surface(bool) const;
	propagate_roi(CA::Bounds const&);
	~ShadowNode();

};
struct CA::OGL::Shape::FlatteningIterator
{

};
struct CA::OGL::Shape::Lines
{

};
struct CA::OGL::SourceRequirement
{

};
struct CA::OGL::Surface
{

};
struct CA::OGL::TextureEdgeMode
{

};
struct CA::OGL::TextureFilter
{

};
struct CA::OGL::TextureFunction
{

};
struct CA::OGL::TransitionNode
{
	TransitionNode(CA::OGL::Renderer&, CA::OGL::Layer*, CA::Transform const&, CA::OGL::ImagingNode*, CA::OGL::ImagingNode*, CA::Render::Transition*);
	apply(float, CA::OGL::Surface**, float*);
	compute_dod(CA::Bounds&);
	needs_surface(bool) const;
	propagate_roi(CA::Bounds const&);
	~TransitionNode();

};
struct CA::OGL::Vertex
{

};
struct CA::RadixSortDoubleItem
{

};
struct CA::RadixSortItem
{

};
struct CA::Rect
{
	double x, y, width, height;
	Rect(CA::Bounds const&);
	Rect(CGRect const&);
	apply_transform(CA::SimpleTransform const&);
	apply_transform(CA::Transform const&);
	apply_transform(CGAffineTransform const&);
	apply_transform_interior(CA::Transform const&);
	is_integral() const;
	is_integral(double) const;
	operator=(CA::Bounds const&);
	operator=(CGRect const&);
	round_center();
	round_inwards();
	set_corners_interior(CA::Vec2<double> const*);
	unapply_inverse_transform(CA::Transform const&);
	unapply_transform(CA::SimpleTransform const&);
	unapply_transform(CA::Transform const&);

};
struct CA::Render::AlignmentProperty
{

};
struct CA::Render::Animation
{
	CA::Render::Timing* _10;
	int _30;							// flag? from CA::Layer::commit_animations @ 20160425
	void* _40;							// ? from CA::Layer::commit_animations @ 20160425
	Animation();
	Animation(CA::Render::Decoder*);
	apply(CA::Render::AnimationEvaluator&, double, int) const;
	encode(CA::Render::Encoder*) const;
	inverse_map_time(double&, double) const;
	is_time_dependent() const;
	map_time(double&, int*) const;
	next_time(double, float, double&) const;
	set_identifier(__CFString const*);
	show(unsigned int, unsigned int) const;
	validate(CA::Render::Layer*);
	was_added(CA::Render::Handle*);
	was_removed(CA::Render::Handle*);
	~Animation();

};
struct CA::Render::AnimationEvaluator
{
	copy_transition();
	first_pass();
	second_pass();

};
struct CA::Render::Array
{
	check_types(unsigned long, CA::Render::Type const*) const;
	decode(CA::Render::Decoder*, unsigned long, CA::Render::Type const*);
	encode(CA::Render::Encoder*) const;
	finalize();
	new_array(unsigned int, CA::Render::Object* const*, bool, unsigned int);
	show(unsigned int, unsigned int) const;
	subarray(unsigned int, unsigned int) const;
	type() const;
	~Array();

};
struct CA::Render::BackdropBuffer
{

};
struct CA::Render::BackdropGroup
{
	struct Item;
	BackdropGroup(CA::Render::Context*, CA::Render::String const*, float);
	add_layer(CA::Render::BackdropState*, CA::Render::LayerNode*, CA::Bounds const&, unsigned int);
	clear_invalid_shape();
	finalize_update(unsigned int);
	has_consistent_background_color();
	invalidate(CA::Shape const*);
	invalidate_buffers(void*);
	invalidate_update(unsigned int);
	layer_item(CA::Render::BackdropState*, unsigned int);
	merge_filters(CA::Render::TypedArray<CA::Render::Filter>*, CA::Rect&);
	retain_group(CA::Render::Context*, CA::Render::String const*, float);
	retain_group_common(CA::Render::Context*, CA::Render::String const*, float, CA::Render::BackdropGroup**, unsigned int, bool);
	set_buffer(CA::Render::BackdropBuffer*);
	set_master_layer(CA::Render::BackdropState*, unsigned int, unsigned int);
	sweep_buffers(unsigned int);
	type() const;
	unref_group_list_isolated(CA::Render::Update*);
	~BackdropGroup();

};
struct CA::Render::BackdropGroup::Item
{

};
struct CA::Render::BackdropLayer
{
	BackdropLayer();
	BackdropLayer(CA::Render::BackdropLayer const&);
	BackdropLayer(CA::Render::Decoder*);
	commit_layer(CA::Render::Context*, CA::Render::Layer*, CA::Render::Handle*, unsigned int);
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_backdrop_bounds(CA::Render::Layer*, CA::Rect&) const;
	get_bounds(CA::Render::Layer*, CA::Rect&, CA::Rect*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	has_background(CA::Render::Layer*, bool&) const;
	hit_test(CA::Render::Layer*, CA::Vec2<double> const&) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	update(CA::Render::Update*, CA::Render::LayerNode*, double);
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	~BackdropLayer();

};
struct CA::Render::BackdropState
{
	collect(unsigned int);
	copy_isolated(CA::Render::Update*);
	retain_state(CA::Render::Context*, unsigned long, CA::Render::String const*, float);
	set_statistics(CA::Render::Layer*, double const*, double);
	type() const;
	~BackdropState();

};
struct CA::Render::BasicAnimation
{
	BasicAnimation(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	time_function(double) const;
	type() const;
	~BasicAnimation();

};
struct CA::Render::BasicAnimation0
{
	BasicAnimation0();
	BasicAnimation0(CA::Render::Decoder*);
	apply(CA::Render::AnimationEvaluator&, double, int) const;
	encode(CA::Render::Encoder*) const;
	interpolate_vector(unsigned long, double*, double const*, double const*, double const*, double const*, CA::Render::ValueInterpolator const&) const;
	validate(CA::Render::Layer*);
	~BasicAnimation0();

};
struct CA::Render::Behavior
{
	Behavior();
	Behavior(CA::Render::Behavior const&);
	Behavior(CA::Render::Decoder*);
	advance(CA::Render::LayerNode*, double, CA::Render::Update*, CA::Render::Context*);
	commit_layer(CA::Render::Context*, CA::Render::Layer*, unsigned int);
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	~Behavior();

};
struct CA::Render::CFObject
{
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	show(unsigned int, unsigned int) const;
	type() const;
	~CFObject();

};
struct CA::Render::CachedHandle
{

};
struct CA::Render::Coder
{
	struct Attachment;
	set_error();
	~Coder();

};
struct CA::Render::Coder::Attachment
{

};
struct CA::Render::CompressedImage
{
	CompressedImage(int, int, CA::Render::CompressedImageFormat, void const*, unsigned long, unsigned long*, unsigned long*, int, void(*)(void const*, void*), void*);
	caches_encoding() const;
	data_size() const;
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	finalize();
	new_image(void const*, unsigned long, void(*)(void const*, void*), void*);
	ref_image_data();
	show(unsigned int, unsigned int) const;
	type() const;
	unref_image_data();
	~CompressedImage();

};
struct CA::Render::CompressedImageFormat
{

};
struct CA::Render::Context
{
	int32_t _8;									// flag, from CA::Context::connect_local @ 20160504
	int32_t _c;									// flag, from CA::Context::connect_local @ 20160504
	pthread_mutex_t _28;						// from CA::Context::new_slot @ 20160504
	struct ResourceTable;
	Context(__CFDictionary const*, unsigned int, unsigned int);
	add_animation(unsigned long, CA::Render::Animation*);
	add_input_time(double);
	before_set_layer(unsigned long);
	block_server_port();
	context_by_client_port(unsigned int);
	context_by_id(unsigned int);
	context_by_server_port(unsigned int);
	context_by_server_port(unsigned int, unsigned int);
	copy_all_contexts();
	copy_dirty_shape();
	copy_slot(unsigned int);
	defer_update();
	delete_layer_shmem_blocks();
	delete_object(unsigned long, unsigned int);
	delete_slot(unsigned int);
	destroy();
	destroy_layer_host();
	destroy_updater();
	did_commit(bool, bool);
	flush_image_queue(unsigned long);
	get_backdrop_layer_statistics(unsigned long, double*);
	get_debug_log(CA::Render::Object*, void*, void*);
	get_layer_renderer_info(unsigned long, unsigned int, int&, unsigned int&, unsigned int&);
	get_layer_shmem(unsigned long, CA::Render::ShmemPtr<CA::Render::LayerShmem>&);
	hit_test(CA::Vec2<double> const&, unsigned int);
	init_updater();
	insecure_process_ids();
	invalidate(CA::Bounds const&);
	invalidate(CA::Shape const*);
	invalidate_layer_shmem(CA::Render::ShmemPtr<CA::Render::LayerShmem>&);
	lookup_cached_handle(CA::Render::Context*, unsigned long, CA::Render::CachedHandle&);
	lookup_cached_handle_(unsigned long, CA::Render::CachedHandle&);
	lookup_handle(unsigned long, unsigned int, bool, unsigned int*);
	lookup_object(unsigned long, unsigned int, CA::Render::Type);
	mark_changed(bool);
	needs_defer_update() const;
	needs_defer_update_locked() const;
	new_image_slot(unsigned int, unsigned int, bool);
	new_slot();
	order_level(float);
	order_relative(bool, unsigned int);
	process_id() const;
	process_name();
	remove_all_animations(unsigned long);
	remove_animation(unsigned long, __CFString const*);
	reset_dirty_shape();
	retain_host_context();
	root_layer();
	root_layer_handle();
	root_layer_node();
	secure_mode_violations();
	server_port();
	set_display_info(unsigned int);
	set_fence(unsigned int, bool, unsigned int);
	set_fence(unsigned int, bool, unsigned int, unsigned int);
	set_layer_id(unsigned long);
	set_object(unsigned long, unsigned int, CA::Render::Object*, unsigned int);
	set_slot(unsigned int, CA::Render::Object*);
	set_updated_seed(unsigned int);
	synchronize(unsigned int, int);
	type() const;
	unblock_server_port();
	update_layer(unsigned long);
	will_commit();
	~Context();

};
struct CA::Render::Context::ResourceTable
{
	insert(unsigned long, unsigned int, CA::Render::Object*);
	lookup(unsigned long);
	release_value(CA::Render::Object*);
	remove(unsigned long, unsigned int);
	remove_all();
	~ResourceTable();

};
struct CA::Render::Decoder
{
	Decoder(x_heap_struct*, CA::Render::Context*, void const*, unsigned long);
	decode_array_object(unsigned long, CA::Render::Type const*);
	decode_atom();
	decode_bytes(void*, unsigned long);
	decode_cfobject();
	decode_cgfloat();
	decode_cgfloat(double*, unsigned long);
	decode_data(void*, unsigned long, unsigned long&, unsigned long);
	decode_data_async(unsigned long&, void(*&)(void const*, void*), void*&);
	decode_double(double*, unsigned long);
	decode_float(float*, unsigned long);
	decode_int16();
	decode_int32();
	decode_int64();
	decode_int8();
	decode_keypath();
	decode_object(CA::Render::Type);
	decode_object(unsigned long, CA::Render::Type const*);
	decode_port(unsigned int*, bool&);
	decode_size_t();
	decode_texture();
	decode_vm_size_t();
	set_attachments(CA::Render::Coder::Attachment**, unsigned long);

};
struct CA::Render::DistanceFieldLayer
{
	DistanceFieldLayer();
	DistanceFieldLayer(CA::Render::Decoder*);
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	preserves_contents_opacity(CA::Render::Layer*) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	~DistanceFieldLayer();

};
struct CA::Render::DynamicsBehavior
{
	DynamicsBehavior();
	DynamicsBehavior(CA::Render::Decoder*);
	DynamicsBehavior(CA::Render::DynamicsBehavior const&);
	advance_impl(CA::Render::LayerNode*, double, CA::Render::Update*, CA::Render::Context*);
	commit_layer(CA::Render::Context*, CA::Render::Layer*, unsigned int);
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	visit_behavior(CA::Render::BehaviorVisitor const&);
	~DynamicsBehavior();

};
struct CA::Render::DynamicsSolver
{
	struct SpringLayer;
	advance(CA::Render::DynamicsBehavior*, CA::Render::LayerNode*, double, CA::Render::Update*, CA::Render::Context*);
	solver(unsigned int, unsigned int);
	type() const;
	~DynamicsSolver();

};
struct CA::Render::DynamicsSolver::SpringLayer
{

};
struct CA::Render::EmitterBehavior
{
	EmitterBehavior();
	EmitterBehavior(CA::Render::Decoder*);
	EmitterBehavior(CA::Render::EmitterBehavior const*);
	encode(CA::Render::Encoder*) const;
	eval();
	get_property(unsigned long, unsigned int const*, unsigned long, double*) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	~EmitterBehavior();

};
struct CA::Render::EmitterBehaviors::AlignToMotion
{
	AlignToMotion(CA::Render::KeyValueArray const*);
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	~AlignToMotion();

};
struct CA::Render::EmitterBehaviors::Attractor
{
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	~Attractor();

};
struct CA::Render::EmitterBehaviors::ColorOver<CA::Render::EmitterBehaviors::DistanceFunction>
{
	ColorOver(CA::Render::KeyValueArray const*);
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	prepare() const;
	~ColorOver();

};
struct CA::Render::EmitterBehaviors::ColorOver<CA::Render::EmitterBehaviors::LifeFunction>
{
	ColorOver(CA::Render::KeyValueArray const*);
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	prepare() const;
	~ColorOver();

};
struct CA::Render::EmitterBehaviors::Drag
{
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	~Drag();

};
struct CA::Render::EmitterBehaviors::Light
{
	Light(CA::Render::KeyValueArray const*);
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	~Light();

};
struct CA::Render::EmitterBehaviors::NoOp
{
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	prepare() const;
	~NoOp();

};
struct CA::Render::EmitterBehaviors::ValueOver<CA::Render::EmitterBehaviors::DistanceFunction>
{
	ValueOver(CA::Render::KeyValueArray const*);
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	prepare() const;
	~ValueOver();

};
struct CA::Render::EmitterBehaviors::ValueOver<CA::Render::EmitterBehaviors::LifeFunction>
{
	ValueOver(CA::Render::KeyValueArray const*);
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	prepare() const;
	~ValueOver();

};
struct CA::Render::EmitterBehaviors::Wave
{
	Wave(CA::Render::KeyValueArray const*);
	operator()(CA::Render::EmitterState::Particle*, CA::Vec3<float>&, CA::Vec4<float>&) const;
	~Wave();

};
struct CA::Render::EmitterCell
{
	EmitterCell();
	EmitterCell(CA::Render::Decoder*);
	EmitterCell(CA::Render::EmitterCell const*);
	encode(CA::Render::Encoder*) const;
	type() const;
	~EmitterCell();

};
struct CA::Render::EmitterLayer
{
	EmitterLayer();
	EmitterLayer(CA::Render::Decoder*);
	EmitterLayer(CA::Render::EmitterLayer const&);
	commit_layer(CA::Render::Context*, CA::Render::Layer*, CA::Render::Handle*, unsigned int);
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_bounds(CA::Render::Layer*, CA::Rect&, CA::Rect*) const;
	get_keypath_object(void* const*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	get_volume(CA::Render::Layer*, CA::Volume&) const;
	has_depth() const;
	is_active() const;
	keypath_is_object(void* const*) const;
	set_keypath_object(void* const*, CA::Render::Object*);
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	type() const;
	update(CA::Render::Update*, CA::Render::LayerNode*, double);
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	~EmitterLayer();

};
struct CA::Render::EmitterState
{
	struct Cell;
	struct Cells;
	struct Particle;
	adjust_vector(CA::Vec3<float>&, float, float, float);
	apply_random_deviation(CA::Vec3<float>&, float);
	free_cell_state(Cell*);
	free_cells_state(Cells*);
	grow_particles(Cell*);
	initialize_particle(Particle*, CA::Render::EmitterCell*, Cell*, Particle const*, double);
	point_in_path(CA::Render::Path const*, CA::Vec3<float>&, CA::Vec3<float>&, float, float);
	point_on_circle(CA::Vec3<float>&, CA::Vec3<float>&, float, float);
	point_on_cuboid_outline(CA::Vec3<float>&, CA::Vec3<float>&, float, float, float);
	point_on_cuboid_surface(CA::Vec3<float>&, CA::Vec3<float>&, float, float, float);
	point_on_path(CA::Render::Path const*, CA::Vec3<float>&, CA::Vec3<float>&, float, float, float);
	point_on_rectangle(CA::Vec3<float>&, CA::Vec3<float>&, float, float, float);
	point_on_sphere(CA::Vec3<float>&, CA::Vec3<float>&, float);
	prepare_cell_state(unsigned long, Cells*);
	retain_state(CA::Render::Context*, unsigned long);
	shrink_particles(Cell*);
	type() const;
	update(CA::Render::EmitterLayer*, double);
	update_cells(double, double&, CA::Render::TypedArray<CA::Render::EmitterCell>*, Cells*, Particle*, float);
	update_particle(float, CA::Render::EmitterCell*, Particle*, float*, std::__1::vector<CA::Render::EmitterBehavior::Eval const*, std::__1::allocator<CA::Render::EmitterBehavior::Eval const*> > const&, unsigned int);
	~EmitterState();

};
struct CA::Render::EmitterState::Cell
{

};
struct CA::Render::EmitterState::Cells
{

};
struct CA::Render::EmitterState::Particle
{

};
struct CA::Render::Encoder
{
	struct SomeWhat
	{
		SomeWhat* _0;		// next
		int64_t _8;			// ?type
		mach_port _10;		// send;
		mach_port _14;		// reply
		int _18;			// bool type
	};

	x_heap_struct* _0;
	uintptr_t _8;
	uintptr_t _10;				// free_buffer_begin
	uintptr_t _18;				// free_buffer_current
	uintptr_t _20;				// free_buffer_limit
	uintptr_t _28;
	uintptr_t _30;					// count of _28 (which is a link of some thing)
	uintptr_t _38;

	struct ObjectCache;
	Encoder(x_heap_struct*, unsigned int, void*, unsigned int, double);
	void encode_atom(unsigned int);
	void encode_bytes(void const*, unsigned long);
	void encode_cfobject(void const*);
	void encode_data(void const*, unsigned long);
	void encode_data_async(void const*, unsigned long, void(*)(void const*, void*), void*);
	void encode_double(double const*, unsigned long);
	void encode_float(float const*, unsigned long);
	void encode_int16(unsigned short);
	void encode_int32(unsigned int);
	void encode_int64(unsigned long long);
	void encode_int8(unsigned char);
	void encode_keypath(void* const*);
	void encode_object(CA::Render::Object const*);
	void encode_object_uncached(CA::Render::Object const*);
	void encode_port(unsigned int, unsigned int, bool);
	grow(unsigned long);
	void receive_reply(unsigned int);
	retain_object(CA::Render::Object const*);
	void send_message(unsigned int, unsigned int);
	set_object_cache(ObjectCache*);
	~Encoder();

};
struct CA::Render::Encoder::ObjectCache
{
	ObjectCache();
	encode(CA::Render::Encoder*, CA::Render::Object const*);
	encode_invalidations(CA::Render::Encoder*);
	invalidate(CA::Render::Object const*);
	is_cached(CA::Render::Object const*);
	mark_volatile(CA::Render::Object const*);
	~ObjectCache();

};
struct CA::Render::Filter
{
	Filter(unsigned int, CA::Render::String*, CA::Render::KeyValueArray*);
	apply_bgimage_dod(CA::Render::Layer*, CA::Rect&) const;
	apply_dod(CA::Render::Layer*, CA::Rect&) const;
	compositing_dod() const;
	compositing_preserves_opacity() const;
	copy() const;
	copy_with_inputs(CA::Render::KeyValueArray*) const;
	decode(CA::Render::Decoder*);
	empty_opaque_shape(CA::Render::Layer*) const;
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*) const;
	identity_bgimage_dod(CA::Render::Layer*) const;
	identity_dod(CA::Render::Layer*) const;
	is_blend_mode() const;
	is_identity(CA::Render::Layer*) const;
	is_source_over() const;
	opaque_shape(CA::Render::Layer*, CA::Rect&) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	shared_filter(unsigned int);
	show(unsigned int, unsigned int) const;
	type() const;
	~Filter();

};
struct CA::Render::ForceField
{
	ForceField();
	ForceField(CA::Render::Decoder*);
	ForceField(CA::Render::ForceField const&);
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	~ForceField();

};
struct CA::Render::Function
{
	decode(CA::Render::Decoder*);
	name() const;
	type() const;

};
struct CA::Render::FunctionName
{

};
struct CA::Render::Gradient
{
	Gradient(CA::Render::Decoder*);
	Gradient(CA::Render::Gradient const&);
	Gradient(unsigned long, bool);
	function_type() const;
	set_color(unsigned long, double const*);
	set_colors(__CFArray const*, CGColorSpace*);
	set_colors(double const*);
	~Gradient();

};
struct CA::Render::GradientLayer
{
	GradientLayer(CA::Render::Decoder*);
	GradientLayer(CA::Render::GradientLayer const&);
	GradientLayer(unsigned int, bool);
	color_map(bool) const;
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	has_background(CA::Render::Layer*, bool&) const;
	hit_test(CA::Render::Layer*, CA::Vec2<double> const&) const;
	is_opaque() const;
	is_valid() const;
	set_color_map(CA::Render::Object*);
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	type() const;
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	~GradientLayer();

};
struct CA::Render::GroupAnimation
{
	GroupAnimation(CA::Render::Decoder*);
	apply(CA::Render::AnimationEvaluator&, double, int) const;
	encode(CA::Render::Encoder*) const;
	type() const;
	validate(CA::Render::Layer*);
	~GroupAnimation();

};
struct CA::Render::Handle
{
	struct Dependence;
	Handle();
	add_animation(CA::Render::Animation*);
	add_dependence(Dependence*);
	add_renderer_info(unsigned int, int, unsigned int, unsigned int);
	before_commit(unsigned int, CA::Render::Layer*);
	collect_animations(double, float);
	copy_animations(bool);
	ensure_behavior_state();
	freeze_thaw(unsigned int, CA::Render::Layer*);
	freeze_thaw_layer(CA::Render::Layer*, bool);
	freeze_thaw_sublayers(CA::Render::Layer*, bool);
	invalidate();
	invalidate_frozen_image();
	invalidate_node();
	is_frozen() const;
	lock_context();
	mark_dependences(CA::Render::LayerNode*);
	remove_all_animations();
	remove_animation(__CFString const*);
	remove_dependence(Dependence*);
	reset_renderer_info();
	retain_context();
	set_current_layer(CA::Render::Layer*, unsigned int);
	set_update_flags(unsigned int);
	type() const;
	unlock_context(CA::Render::Context*);
	unmark_all_dependences();
	~Handle();

};
struct CA::Render::Handle::Dependence
{

};
struct CA::Render::Image
{
	struct SubimageKey;
	struct TiledImage;
	caches_encoding() const;
	collect_subimages(double);
	collect_subimages_(SubimageKey*, CA::Render::Image*, void*);
	copy_cgimage() const;
	copy_subimage(unsigned int, CA::Bounds const&, unsigned long, bool);
	copy_tiled_texture(unsigned long, bool);
	data(unsigned int) const;
	data_size() const;
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	finalize();
	finalize_subimages();
	finalize_tiled_images();
	get_tiled_texture_size(unsigned int&, unsigned int&);
	height(unsigned int) const;
	image_format() const;
	implicitly_opaque() const;
	new_image(unsigned int, unsigned int, unsigned int, unsigned int, CGColorSpace*, CA::Render::Shmem*, unsigned long const*);
	new_image(unsigned int, unsigned int, unsigned int, unsigned int, CGColorSpace*, void const*, unsigned long const*, void(*)(void const*, void*), void*);
	ogl_image_key() const;
	ref_image_data();
	release_data() const;
	set_data_volatile(bool);
	set_default_colorspace();
	should_tile_texture() const;
	show(unsigned int, unsigned int) const;
	tiled_image_mutex_init();
	type() const;
	unref_image_data();
	width(unsigned int) const;
	~Image();

};
struct CA::Render::Image::SubimageKey
{
	delete_images(CA::Render::Image::SubimageKey*, CA::Render::Image*, void*);

};
struct CA::Render::Image::TiledImage
{
	struct Key;
	TiledImage(CA::Render::Image*, unsigned int, unsigned int, unsigned long, bool);
	copy_subtexture(int, unsigned int, unsigned int, int, int, unsigned int, unsigned int, double, float&, unsigned int&);
	finalize();
	free_tile(Key*, CA::Render::Image*, void*);
	image_format() const;
	type() const;
	will_deallocate(CA::Render::Object*, void*, void*);
	~TiledImage();

};
struct CA::Render::Image::TiledImage::Key
{
	compare(CA::Render::Image::TiledImage::Key*, CA::Render::Image::TiledImage::Key*);
	hash(CA::Render::Image::TiledImage::Key*);

};
struct CA::Render::ImageCacheEntry
{

};
struct CA::Render::ImageFilter
{

};
struct CA::Render::ImageProvider
{
	ImageProvider(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool, float, int);
	add_needed(CA::Render::ImageProviderKey const&, int, CA::Render::ImageProviderSubImage*);
	collect(double, bool);
	copy_subtexture(int, unsigned int, unsigned int, int, int, unsigned int, unsigned int, double, float&, unsigned int&);
	create(CA::Render::Context*, unsigned long, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool, float, int, unsigned int, CA::Render::Pattern*);
	generate_subtexture(int, unsigned int, unsigned int, bool, unsigned int, double, unsigned int&);
	implicitly_opaque() const;
	invalidate(CA::Render::Context*, unsigned long, int, int, int, int, unsigned int, unsigned int);
	invalidate(int, int, int, int, unsigned int, unsigned int);
	invalidate_context();
	needed_subimage(CA::Render::Context*, unsigned long, unsigned int&, unsigned int&, unsigned int&, unsigned int&);
	prefetch_border() const;
	prefetch_subtexture(int, unsigned int, unsigned int, int, unsigned int, double);
	set_fill_color(CA::Render::Context*, unsigned long, unsigned int, CA::Render::Pattern*);
	set_image_size(CA::Render::Context*, unsigned long, unsigned int, unsigned int);
	set_max_tile_scale(CA::Render::Context*, unsigned long, int);
	set_subimage(CA::Render::Context*, unsigned long, int, unsigned int, unsigned int, CA::Render::Texture*, unsigned int, unsigned int);
	set_subimage(int, unsigned int, unsigned int, CA::Render::Texture*, unsigned int, unsigned int);
	show(unsigned int, unsigned int) const;
	signal_client();
	type() const;
	~ImageProvider();

};
struct CA::Render::ImageProviderKey
{

};
struct CA::Render::ImageProviderSubImage
{

};
struct CA::Render::ImageQueue
{
	ImageQueue(CA::Render::Shmem*);
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	flush();
	flush_cache();
	set_client_port(unsigned int);
	set_detached_flag(bool);
	set_displayed_pixel_count(unsigned int);
	set_rotation_flags(unsigned int);
	show(unsigned int, unsigned int) const;
	texture_cast();
	type() const;
	update(CA::Render::Context*, CA::Render::Context*, double, float, X::List<CA::Render::Timing*>*, CA::Render::Update*);
	~ImageQueue();

};
struct CA::Render::InterpolatedFunction
{
	InterpolatedFunction(CA::Render::Decoder*);
	InterpolatedFunction(CA::Render::InterpolatedFunction const&);
	InterpolatedFunction(unsigned long, unsigned int, bool);
	apply(unsigned long, double const*, long, double*, long, double(*)(unsigned int, unsigned int const*, unsigned long, void*), void*) const;
	encode(CA::Render::Encoder*) const;
	function_type() const;
	input_count() const;
	output_count() const;
	sample(float, float*) const;
	set_location(unsigned long, float);
	set_locations(__CFArray const*);
	set_locations(double const*);
	set_values(double const*);
	~InterpolatedFunction();

};
struct CA::Render::Interpolator
{
	Interpolator(CA::Render::Object*, CA::Render::Object*, CA::Render::Object*, CA::Render::Object*, CA::Render::ValueInterpolator const&);
	Interpolator(CA::Render::Object*, CA::Render::Object*, double);
	show(unsigned int, unsigned int) const;
	type() const;
	~Interpolator();

};
struct CA::Render::KeyValue
{
	KeyValue(CA::Render::Decoder*);
	KeyValue(unsigned int, CA::Render::Object*);
	encode(CA::Render::Encoder*) const;
	show(unsigned int, unsigned int) const;
	type() const;
	~KeyValue();

};
struct CA::Render::KeyValueArray
{
	find_named_object_(CA::Render::KeyValueArray const*, unsigned int);
	get_atom_key(unsigned int, unsigned int) const;
	get_color_key(unsigned int, unsigned int) const;
	get_float_color_key(unsigned int, float*) const;
	get_float_key(unsigned int, double) const;
	get_int_key(unsigned int, int) const;
	get_key(unsigned int) const;
	get_rect_key(CA::Rect&, unsigned int) const;
	get_rect_key(unsigned int, CA::Rect const&) const;
	get_vec2_key(unsigned int, CA::Vec2<double> const&) const;
	get_vec3_key(unsigned int, CA::Vec3<double> const&) const;
	get_vec4_key(unsigned int, CA::Vec4<double> const&) const;
	set_key(unsigned int, CA::Render::Object*);

};
struct CA::Render::KeyframeAnimation
{
	KeyframeAnimation();
	KeyframeAnimation(CA::Render::Decoder*);
	apply(CA::Render::AnimationEvaluator&, double, int) const;
	encode(CA::Render::Encoder*) const;
	keyframe_for_time(double, double*) const;
	next_time(double, float, double&) const;
	type() const;
	update_paced_key_times();
	~KeyframeAnimation();

};
struct CA::Render::Layer
{
	struct Ext;
	Layer();
	Layer(CA::Render::Decoder*);
	Layer(CA::Render::Layer const&);
	anchor_point() const;
	append_contents_transform(CA::Transform&, CA::Vec2<double> const&, CA::Vec2<double>*) const;
	apply_contents_transform(CA::Rect&, CA::Vec2<double> const&) const;
	composite(CA::Render::Layer* const*, unsigned long, bool);
	compute_frame_offset(CA::Render::Layer const*, double*) const;
	compute_frame_transform(CA::Render::Layer const*, CA::Mat4<double>&, double const*, CA::Mat4<double> const*) const;
	compute_light_transform(CA::Mat4<float>&) const;
	copy_properties(CA::Render::Layer*, unsigned int);
	cow_subclass();
	encode(CA::Render::Encoder*) const;
	ensure_ext();
	frame(CA::Render::Layer*) const;
	get_keypath_object(void* const*);
	get_keypath_value(void* const*, unsigned long, double*, double**);
	get_property_value(unsigned int const*, unsigned long, unsigned long, double*, double**) const;
	gravity_from_string(__CFString const*);
	image_filter_from_string(__CFString const*, bool);
	is_animating(double, double, float, double, double, float, unsigned int, double&) const;
	keypath_is_object(void* const*);
	layer_contents_transform(CA::Vec2<double> const&, CGAffineTransform&) const;
	set_affine_matrix(X::Ref<CA::Render::Vector> Ext::*, bool, unsigned long, double const*);
	set_anchor_point(CA::Vec2<double> const&);
	set_anchor_point_z(double);
	set_background_color_phase(CA::Vec2<double> const&);
	set_background_filters(CA::Render::TypedArray<CA::Render::Filter>*);
	set_background_pattern(CA::Render::Pattern*);
	set_behaviors(CA::Render::TypedArray<CA::Render::Behavior>*);
	set_border_color(unsigned int);
	set_border_pattern(CA::Render::Pattern*);
	set_border_width(float);
	set_compositing_filter(CA::Render::Filter*);
	set_contents_center(CA::Render::Vector*);
	set_contents_rect(CA::Render::Vector*);
	set_contents_scale(float);
	set_contents_transform(CA::Render::Vector*);
	set_corner_contents_center(CA::Render::Vector*);
	set_corner_radius(float);
	set_filters(CA::Render::TypedArray<CA::Render::Filter>*);
	set_keypath_object(void* const*, CA::Render::Object*);
	set_keypath_value(void* const*, bool, unsigned long, double const*);
	set_lights(CA::Render::TypedArray<CA::Render::Light>*);
	set_lod_bias(float);
	set_mask(CA::Render::Layer*);
	set_mass(float);
	set_material(CA::Render::Material const&);
	set_mesh_transform(CA::Render::MeshTransform*);
	set_moment_of_inertia(float);
	set_motion_blur_amount(float);
	set_name(CA::Render::String*);
	set_property_value(unsigned int const*, unsigned long, bool, unsigned long, double const*);
	set_rasterization_scale(float);
	set_restitution(float);
	set_shadow_color(unsigned int);
	set_shadow_offset(CA::Vec2<float> const&);
	set_shadow_path(CA::Render::Path*);
	set_shadow_radius(float);
	set_subclass(CA::Render::LayerSubclass*);
	set_sublayer_transform(CA::Render::Vector*);
	set_timing(CA::Render::Timing*);
	set_transform(CA::Render::Vector*);
	set_transform_matrix(X::Ref<CA::Render::Vector> Ext::*, bool, unsigned long, double const*);
	set_velocity_stretch(float);
	set_z_position(double);
	show(unsigned int, unsigned int) const;
	string_from_gravity(CA::Render::LayerGravity);
	type() const;
	~Layer();

};
struct CA::Render::Layer::Ext
{
	Ext(CA::Render::Decoder*);
	Ext(CA::Render::Layer::Data const&);
	Ext(CA::Render::Layer::Ext const&);
	encode(CA::Render::Encoder*) const;
	unref();
	~Ext();

};
struct CA::Render::LayerBehaviorState
{
	begin(CA::Render::Handle*, CA::Render::LayerNode*, CA::Render::Update*);
	commit(CA::Render::Handle*, CA::Render::LayerNode*, CA::Render::Update*);
	concat_motion_transform(CA::Mat4<double>&, CA::Render::Layer const*) const;
	~LayerBehaviorState();

};
struct CA::Render::LayerGravity
{

};
struct CA::Render::LayerHost
{
	LayerHost(CA::Render::Decoder*);
	LayerHost(unsigned int);
	commit_layer(CA::Render::Context*, CA::Render::Layer*, CA::Render::Handle*, unsigned int);
	did_commit(CA::Render::Context*, CA::Render::Context*, bool, bool);
	encode(CA::Render::Encoder*) const;
	invalidate() const;
	is_secure() const;
	retain_hosted_context(CA::Render::Context*) const;
	show(unsigned int, unsigned int) const;
	type() const;
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	will_commit(CA::Render::Context*);
	~LayerHost();

};
struct CA::Render::LayerNode
{
	before(CA::Render::LayerNode*);
	clear_above_and_black_below(bool) const;
	clip_node(double const*);
	copy_motion_blur_end_point_(float);
	copy_motion_blur_start_point_(float);
	copy_node();
	delete_node(CA::Render::LayerNode*);
	depth_sort_sublayers(bool);
	hit_test_(CA::Vec2<double> const&, unsigned int);
	new_node();
	set_frame_transform(CA::Transform const&);
	shared_ancestor(CA::Render::LayerNode*);
	split_node(double const*);
	update_frame_transform();
	update_z_range();

};
struct CA::Render::LayerSubclass
{
	commit_layer(CA::Render::Context*, CA::Render::Layer*, CA::Render::Handle*, unsigned int);
	copy() const;
	get_bounds(CA::Render::Layer*, CA::Rect&, CA::Rect*) const;
	get_keypath_object(void* const*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	get_volume(CA::Render::Layer*, CA::Volume&) const;
	has_background(CA::Render::Layer*, bool&) const;
	has_depth() const;
	hit_test(CA::Render::Layer*, CA::Vec2<double> const&) const;
	keypath_is_object(void* const*) const;
	preserves_contents_opacity(CA::Render::Layer*) const;
	self_intersects(CA::Render::Layer*) const;
	set_keypath_object(void* const*, CA::Render::Object*);
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	update(CA::Render::Update*, CA::Render::LayerNode*, double);

};
struct CA::Render::Light
{
	Light();
	Light(CA::Render::Decoder*);
	Light(CA::Render::Light const&);
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*) const;
	set_cone(float, float);
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	~Light();

};
struct CA::Render::LineCap
{

};
struct CA::Render::LineJoin
{

};
struct CA::Render::MatchMoveAnimation
{
	struct Dependence;
	MatchMoveAnimation();
	MatchMoveAnimation(CA::Render::Decoder*);
	apply(CA::Render::AnimationEvaluator&, double, int) const;
	encode(CA::Render::Encoder*) const;
	is_time_dependent() const;
	set_property(void* const*);
	show(unsigned int, unsigned int) const;
	type() const;
	validate(CA::Render::Layer*);
	was_added(CA::Render::Handle*);
	was_removed(CA::Render::Handle*);
	~MatchMoveAnimation();

};
struct CA::Render::MatchMoveAnimation::Dependence
{
	run(CA::Render::Update*);
	~Dependence();

};
struct CA::Render::MeshEdge
{

};
struct CA::Render::MeshFace
{

};
struct CA::Render::MeshTransform
{
	MeshTransform(CA::Render::Decoder*);
	MeshTransform(CA::Render::MeshTransform const*);
	MeshTransform(unsigned long, unsigned long, int);
	apply_rect(CA::Rect const&, CA::Rect const&) const;
	apply_volume(CA::Rect const&, CA::Rect const&) const;
	bounds(CA::Rect const&) const;
	distance_to(CA::Render::Object const*) const;
	encode(CA::Render::Encoder*) const;
	eval_interpolator(CA::Render::Interpolator*, CA::Rect const&);
	frame(CA::Rect const&) const;
	mix(CA::Render::Object*, CA::Render::Object*, CA::Render::Object*, CA::Render::ValueInterpolator const&);
	mix(CA::Render::Object*, CA::Render::ValueInterpolator const&);
	retain_subdivided_mesh(int) const;
	show(unsigned int, unsigned int) const;
	subdivide(int);
	type() const;
	unapply_rect(CA::Rect const&, CA::Rect const&) const;
	update(unsigned int) const;
	update_locked(unsigned int) const;
	validate() const;
	validate_locked() const;
	vertex_transform(CA::Rect const&, CA::Vec3<float>&, CA::Vec3<float>&) const;
	~MeshTransform();

};
struct CA::Render::MeshVertex
{

};
struct CA::Render::NamedFunction
{
	apply(unsigned long, double const*, long, double*, long, double(*)(unsigned int, unsigned int const*, unsigned long, void*), void*) const;
	encode(CA::Render::Encoder*) const;
	function_type() const;
	input_count() const;
	name() const;
	new_function(CA::Render::FunctionName);
	output_count() const;
	show(unsigned int, unsigned int) const;
	~NamedFunction();

};
struct CA::Render::NotificationName
{

};
struct CA::Render::Object
{
	cpp_virtbl* _0;
	Object(CA::Render::Decoder*, unsigned int);
	caches_encoding() const;
	can_mix_with_object(CA::Render::Object*);
	distance_to(CA::Render::Object const*) const;
	encode(CA::Render::Encoder*) const;
	external_ref() const;
	external_unref() const;
	finalize();
	mix(CA::Render::Object*, CA::Render::Object*, CA::Render::Object*, CA::Render::ValueInterpolator const&);
	mix(CA::Render::Object*, CA::Render::ValueInterpolator const&);
	ogl_image_key() const;
	ref() const;
	refcount() const;
	show(unsigned int, unsigned int) const;
	texture_cast();
	type_name(CA::Render::Type);
	unref() const;
	~Object();

};
struct CA::Render::Path
{
	bounding_rect() const;
	cg_path() const;
	contains(CA::Vec2<double> const&, CA::Render::PathFillRule) const;
	copy_subpath(double, double) const;
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	finalize();
	interpolate(float, CA::Vec2<double>&, double*) const;
	interpolate(int, float, bool, CA::Vec2<double>*, CA::Vec2<double>*, CA::Vec2<double>*, double*) const;
	is_rectangular(CA::Rect*) const;
	keyframe_lengths() const;
	mix(CA::Render::Object*, CA::Render::ValueInterpolator const&);
	new_path(CGPath const*, bool);
	new_path(unsigned int, unsigned int, unsigned int);
	new_path(unsigned long, unsigned int, unsigned char const*, unsigned int, CA::Vec2<double> const*, unsigned int);
	show(unsigned int, unsigned int) const;
	stroke(double, double, CA::Render::LineCap, CA::Render::LineJoin, double, unsigned long, double const*, double) const;
	stroke(double, double, double, double, CA::Render::LineCap, CA::Render::LineJoin, double, unsigned long, double const*, double) const;
	type() const;
	~Path();

};
struct CA::Render::PathFillRule
{

};
struct CA::Render::Pattern
{
	Pattern(CA::Render::Decoder*);
	Pattern(CGPattern*, CGColorSpace*, CA::Vec2<double> const&, unsigned int, double);
	collect(double);
	encode(CA::Render::Encoder*) const;
	is_opaque() const;
	new_pattern(CGPattern*, CGColorSpace*, CGAffineTransform const*, unsigned int, double);
	show(unsigned int, unsigned int) const;
	type() const;
	~Pattern();

};
struct CA::Render::PixelBuffer
{
	PixelBuffer(CA::Render::Shmem*, unsigned int, unsigned int, unsigned long, unsigned int, __CFDictionary const*);
	PixelBuffer(__CVBuffer*, unsigned int, unsigned int);
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	finalize();
	image() const;
	image_format() const;
	implicitly_opaque() const;
	show(unsigned int, unsigned int) const;
	type() const;
	~PixelBuffer();

};
struct CA::Render::PropertyAnimation
{
	PropertyAnimation(CA::Render::Decoder*);
	animation_value(CA::Render::Object*, unsigned long, double*, double**) const;
	encode(CA::Render::Encoder*) const;
	interpolate_vector(unsigned long, double*, double const*, double const*, double const*, double const*, CA::Render::ValueInterpolator const&) const;
	set(CA::Render::Layer*, unsigned long, double const*, double const*, double const*, double const*, double const*, double const*, CA::Render::ValueInterpolator const*, int) const;
	set_property(void* const*);
	validate(CA::Render::Layer*);
	~PropertyAnimation();

};
struct CA::Render::Proxy
{
	Proxy(CA::Render::Decoder*);
	Proxy(unsigned int, unsigned long long);
	copy_object(CA::Render::Context*);
	encode(CA::Render::Encoder*) const;
	show(unsigned int, unsigned int) const;
	type() const;
	~Proxy();

};
struct CA::Render::RenderBuffer
{

};
struct CA::Render::ReplicatorLayer
{
	ReplicatorLayer();
	ReplicatorLayer(CA::Render::Decoder*);
	ReplicatorLayer(CA::Render::ReplicatorLayer const&);
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	~ReplicatorLayer();

};
struct CA::Render::Server::CallbackBehavior
{

};
struct CA::Render::Server::ReceivedMessage
{
	delay_until(double);
	delete_delayed_commands(CA::Render::Object*, void*, void*);
	dispatch();
	run_command_stream();
	run_delayed_commands(double, void*);
	send_reply();
	~ReceivedMessage();

};
struct CA::Render::ShadowCache
{
	struct Entry;
	ShadowCache();
	collect(double);
	fetch(CA::Render::Path*, double, CA::Rect*, CA::Rect*, std::__1::vector<double, std::__1::allocator<double> > const**, std::__1::vector<double, std::__1::allocator<double> > const**, float);
	free_bounds_entry(void*, void*);
	free_entry(CA::Render::Path*, Entry*, void*);
	lookup_path(CA::Rect const&, double);
	path_deleted(CA::Render::Object*, void*, void*);
	~ShadowCache();

};
struct CA::Render::ShadowCache::Entry
{

};
struct CA::Render::ShapeLayer
{
	ShapeLayer();
	ShapeLayer(CA::Render::Decoder*);
	ShapeLayer(CA::Render::ShapeLayer const&);
	copy() const;
	encode(CA::Render::Encoder*) const;
	fill_bounds() const;
	get_bounds(CA::Render::Layer*, CA::Rect&, CA::Rect*) const;
	get_keypath_object(void* const*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	hit_test(CA::Render::Layer*, CA::Vec2<double> const&) const;
	invalidate_stroke_path();
	keypath_is_object(void* const*) const;
	self_intersects(CA::Render::Layer*) const;
	set_keypath_object(void* const*, CA::Render::Object*);
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	stroke_bounds() const;
	stroke_path(double) const;
	type() const;
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	~ShapeLayer();

};
// by hand
struct CA::Render::ShmemBitmap
{
	unsigned int _10;	// ?flag
	float _14;			// width;
	float _18;			// height;
	unsigned int _1c;
	copy_pixels(CA::Render::ShmemBitmap const*, CGSRegionObject*);
	fill_pixels(unsigned int, CGSRegionObject*);
	int lod_width(unsigned int) const;
	int lod_height(unsigned int) const;
	void* lod_data(unsigned int);
	int64_t lod_rowbytes(unsigned int) const;
};
struct CA::Render::Shmem
{
	CA::Render::ShmemBitmap* _18;
	caches_encoding() const;
	copy_cgimage(CGColorSpace*);
	copy_image(CGColorSpace*);
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	is_purged() const;
	is_volatile() const;
	static CA::Render::Shmem* new_bitmap(unsigned int, unsigned int, unsigned int, unsigned int);
	new_shmem(unsigned int, unsigned long, unsigned long long, bool, unsigned int);
	new_shmem(unsigned long);
	new_shmem(void const*, unsigned long, unsigned int, void(*)(void const*, void*), void*);
	offset() const;
	port() const;
	set_volatile(bool, int);
	show(unsigned int, unsigned int) const;
	type() const;
	~Shmem();

};

template<typename _T> 
struct CA::Render::ShmemPtr
{
	CA::Render::Shmem* _Ptr;			// i guess, from CA::Layer::fetch_geometry
	uintptr_t _8;
	void set(CA::Render::Shmem*, unsigned long);
};

struct CA::Render::Spline
{

};
struct CA::Render::Spring
{
	Spring();
	Spring(CA::Render::Decoder*);
	Spring(CA::Render::Spring const&);
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*) const;
	send_did_stop(CA::Render::Context*, CA::Render::DynamicsBehavior*, unsigned int);
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	~Spring();

};
struct CA::Render::SpringAnimation
{
	SpringAnimation();
	SpringAnimation(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	time_function(double) const;
	type() const;
	validate(CA::Render::Layer*);
	~SpringAnimation();

};
struct CA::Render::String
{
	atom(bool) const;
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	equal(CA::Render::String const*) const;
	equal(char const*) const;
	equal(unsigned int) const;
	finalize();
	new_string(__CFString const*);
	new_string(unsigned long, char const*);
	show(unsigned int, unsigned int) const;
	type() const;
	~String();

};
struct CA::Render::SubpixelMaskLayer
{
	SubpixelMaskLayer();
	SubpixelMaskLayer(CA::Render::Decoder*);
	copy() const;
	encode(CA::Render::Encoder*) const;
	get_property(unsigned long, unsigned int const*, unsigned long, double*, double**) const;
	set_property(unsigned long, unsigned int const*, bool, unsigned long, double const*);
	show(unsigned int, unsigned int) const;
	type() const;
	visit_subclass(CA::Render::LayerSubclassVisitor const&) const;
	~SubpixelMaskLayer();

};
struct CA::Render::Surface
{
	Surface(CA::Render::Surface*, unsigned int);
	caches_encoding() const;
	data_size() const;
	decode(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	finalize();
	image_format() const;
	implicitly_opaque() const;
	ogl_image_key() const;
	set_data_volatile(bool);
	set_default_colorspace();
	show(unsigned int, unsigned int) const;
	type() const;
	~Surface();

};
struct CA::Render::Texture
{
	can_mix_with_object(CA::Render::Object*);
	clean_rect() const;
	copy_tiled_texture(unsigned long, bool);
	data_size() const;
	decode(CA::Render::Decoder*);
	displayed_size_(unsigned int&, unsigned int&);
	encode(CA::Render::Encoder*) const;
	get_tiled_texture_size(unsigned int&, unsigned int&);
	has_clean_rect() const;
	image_format() const;
	implicitly_opaque() const;
	mix(CA::Render::Object*, CA::Render::ValueInterpolator const&);
	ref_image_data();
	set_clean_rect(CA::Bounds const&);
	set_colorspace(CGColorSpace*);
	set_data_volatile(bool);
	set_default_colorspace();
	should_tile_texture() const;
	texture_cast();
	tiled_texture_cast();
	unref_image_data();
	~Texture();

};
struct CA::Render::TileCache
{
	TileCache(CA::Render::TileCacheContext const&);
	collect(double);
	collect_entry(CA::Render::Image*, CA::Render::TileCacheEntry*, void*);
	get_image(CA::Render::Image*, double, double, double, double, double);
	image_deleted(CA::Render::Object*, void*, void*);
	~TileCache();

};
struct CA::Render::TileCacheEntry
{

};
struct CA::Render::TiledTexture
{
	generate_subtexture(int, unsigned int, unsigned int, bool, unsigned int, double, unsigned int&);
	lod_height(int);
	lod_scale(int);
	lod_width(int);
	max_lod(unsigned int, unsigned int);
	prefetch_border() const;
	prefetch_subtexture(int, unsigned int, unsigned int, int, unsigned int, double);
	set_fill_color(unsigned int, CA::Render::Pattern*);
	tiled_texture_cast();
	~TiledTexture();

};
struct CA::Render::Timing
{
	double _20;
	Timing();
	Timing(CA::Render::Decoder*);
	encode(CA::Render::Encoder*) const;
	end_time() const;
	inverse_map_time(double&, double) const;
	map_active_to_local(double&, unsigned int*) const;
	map_active_to_parent(double&, double) const;
	map_local_to_active(double&, double) const;
	map_parent_to_active(double&) const;
	map_time(double&, unsigned int*) const;
	next_begin_time(double, float) const;
	parent_duration() const;
	show(unsigned int, unsigned int) const;
	type() const;
	~Timing();

};
struct CA::Render::Transition
{
	Transition(CA::Render::Decoder*);
	Transition(CA::Render::TransitionAnimation const*, double, unsigned int);
	encode(CA::Render::Encoder*) const;
	lookup_transition(unsigned int);
	show(unsigned int, unsigned int) const;
	subclass() const;
	type() const;
	~Transition();

};
struct CA::Render::TransitionAnimation
{
	TransitionAnimation();
	TransitionAnimation(CA::Render::Decoder*);
	apply_transition(CA::Render::Layer*, double, bool&) const;
	encode(CA::Render::Encoder*) const;
	type() const;
	validate(CA::Render::Layer*);
	~TransitionAnimation();

};
struct CA::Render::Type
{

};
struct CA::Render::Update
{
	struct Backdrop;
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
	Update(void*, unsigned long, double, CVTimeStamp const*, unsigned int, unsigned int, CA::Bounds const&, unsigned int);
	add_backdrop_invalidations();
	add_backdrop_layer(CA::Render::Context*, CA::Render::LayerNode*, CA::Render::Handle*, CA::SimpleTransform const&, void*, bool);
	add_context(CA::Render::Context*);
	add_context(CA::Render::Context*, CA::Render::Layer*, CA::Transform const*);
	add_context(CA::Render::Context*, CA::Transform const&);
	add_excluded_context_id(unsigned int);
	added_all_contexts();
	allowed_in_secure_update(CA::Render::Context*, CA::Render::LayerHost const*);
	allowed_to_include_context(CA::Render::Context*) const;
	hit_test(CA::Vec2<double> const&) const;
	invalidate(CA::Bounds const&);
	invalidate(CA::Shape const*);
	invalidate_backdrop_shapes(bool);
	invalidate_backdrops(CA::Bounds const&, CA::Render::BackdropState*);
	invalidate_backdrops(CA::Shape const*, Backdrop*);
	layer_hosting_changed() const;
	print_trees() const;
	release_object(CA::Render::Object*);
	release_objects() const;
	under_backdrop_layer(CA::Render::LayerNode*, CA::Bounds const&) const;
	~Update();

};
struct CA::Render::Update::Backdrop
{
	invalidate(unsigned int);
	~Backdrop();

};
struct CA::Render::Updater::FilterOp
{
	apply_filter(CA::Rect&);
	copy() const;
	map_bounds(CA::Render::Updater::LayerShapes&);
	map_crop(CA::Render::Updater::LayerShapes&);
	unmap_rect(CA::Rect&);
	~FilterOp();

};
struct CA::Render::Updater::FlattenZOp
{
	copy() const;
	is_flatten_z() const;
	map_bounds(CA::Render::Updater::LayerShapes&);
	map_crop(CA::Render::Updater::LayerShapes&);
	unmap_rect(CA::Rect&);
	~FlattenZOp();

};
struct CA::Render::Updater::GlobalState
{

};
struct CA::Render::Updater::LayerShapes
{
	union_bounds(CA::Rect const&);

};
struct CA::Render::Updater::LayerShapesOp
{
	is_flatten_z() const;

};
struct CA::Render::Updater::LocalState
{

};
struct CA::Render::Updater::LocalState0
{

};
struct CA::Render::Updater::MeshOp
{
	copy() const;
	map_bounds(CA::Render::Updater::LayerShapes&);
	map_crop(CA::Render::Updater::LayerShapes&);
	unmap_rect(CA::Rect&);
	~MeshOp();

};
struct CA::Render::Updater::RasterizationOp
{
	copy() const;
	map_bounds(CA::Render::Updater::LayerShapes&);
	map_crop(CA::Render::Updater::LayerShapes&);
	unmap_rect(CA::Rect&);
	~RasterizationOp();

};
struct CA::Render::Updater::ShadowOp
{
	apply_shadow(CA::Rect&);
	copy() const;
	map_bounds(CA::Render::Updater::LayerShapes&);
	map_crop(CA::Render::Updater::LayerShapes&);
	unmap_rect(CA::Rect&);
	~ShadowOp();

};
struct CA::Render::Updater::TransformOp
{
	copy() const;
	map_bounds(CA::Render::Updater::LayerShapes&);
	map_crop(CA::Render::Updater::LayerShapes&);
	unmap_rect(CA::Rect&);
	~TransformOp();

};
struct CA::Render::Vector
{
	affine_transform() const;
	decode(CA::Render::Decoder*);
	distance_to(CA::Render::Object const*) const;
	encode(CA::Render::Encoder*) const;
	finalize();
	get_values(double*) const;
	mix(CA::Render::Object*, CA::Render::Object*, CA::Render::Object*, CA::Render::ValueInterpolator const&);
	mix(CA::Render::Object*, CA::Render::ValueInterpolator const&);
	new_affine_transform(CGAffineTransform const&);
	new_color(CGColor*, CGColorSpace*);
	new_rect(CA::Rect const&);
	new_vector(unsigned int, double const*);
	rect() const;
	show(unsigned int, unsigned int) const;
	transform() const;
	type() const;
	~Vector();

};
struct CA::Render::occlusion_closure
{

};
struct CA::Render::occlusion_data
{

};
struct CA::ScanConverter::FillRule
{

};
struct CA::ScanConverter::Path
{
	Path(x_heap_struct*);
	add_cube(double, double, double, double, double, double, double, double);
	add_cube_clip(double, double, double, double, double, double, double, double, double, double, double, double);
	add_curve(double, double, double, double, double, double, double, double);
	add_line(double, double, double, double);
	add_monotonic_cube(double, double, double, double, double, double, double, double);
	closepath();
	cubeto(double, double, double, double, double, double);
	cubeto(double, double, double, double, double, double, double, double, double);
	lineto(double, double);
	lineto(double, double, double);
	moveto(double, double);
	moveto(double, double, double);
	quadto(double, double, double, double);
	quadto(double, double, double, double, double, double);

};
struct CA::ScanConverter::RendererImpl::Edge
{
	sort_xmin(CA::ScanConverter::RendererImpl::Edge*, unsigned long);

};
struct CA::Shape
{
	Shape(CA::Bounds const&);
	Union(CA::Bounds const&) const;
	Union(CA::Shape const*) const;
	area() const;
	contains(CA::Bounds const&) const;
	dilate(int, int) const;
	equal(CA::Bounds const&) const;
	equal(CA::Shape const*) const;
	get_bounds(CA::Bounds&) const;
	get_interior_bounds(CA::Bounds&) const;
	intersect(CA::Bounds const&) const;
	intersect(CA::Shape const*) const;
	intersects(CA::Bounds const&) const;
	intersects(CA::Shape const*) const;
	is_infinite() const;
	new_shape(CA::Bounds const&);
	operator=(CA::Bounds const&);
	ref() const;
	scale_and_dilate(float, float, int, int) const;
	subtract(CA::Bounds const&) const;
	subtract(CA::Shape const*) const;
	translate(int, int) const;
	unref();

};
struct CA::ShapeHandle
{
	finish(int const*);
	grow(unsigned int);

};
struct CA::Transaction
{
	struct Command;
	struct Continuation;
	struct Fence;
	struct Join;
	struct Level;
	struct Shared;			// by hand, from CA::Layer::layer_at_time @ 20160501

	struct Unknwn_deleted_id
	{
		Unknwn_deleted_id* _0;
		unsigned long _8;
		unsigned int _10;
	};

	static x_hash_table* roots;			// from CA::Transaction::commit @ 20160503
	static OSSpinLock roots_lock;		// from CA::Transaction::commit @ 20160503
	static void* transaction_key;		// from CA::Transaction::observer_callback @ 20160503
	static x_list* global_deleted;
	static int slot_mask;
	static bool _debug_transactions;

	Shared* _0;				// from CA::Layer::layer_at_time @ 20160501, points to transaction->_88
	int _8;					// counter, from layout_if_needed
	x_hash_table* _10;		// ht for thread_flags, from CA::Layer::free_transaction @20160429
	OSSpinLock* _18;		// from CA::Transaction::create @ 20160503
	int _20;				// refcnt of lock, from CA::Transaction::lock @ 20160519
	CA::Transaction::Level* _28;			// level, from CA::Transaction::commit @ 20160519
	x_list* _30;			// list of _Block, from CA::Transaction::pop_animator @ 20160519
	CA::Transaction::Command* _38;			// reversed head, the Shared::_18 keep the want-to-commit, from CA::Transaction::commit @ 20160504
	x_chain* _40;			// deleted, pick up the Shared::_20, then will join global_deleted from CA::Transaction::commit @ 20160519
	X::List<void const*>* _48;	// from CA::Transaction::unlock @ 20160520
	CA::Context* _50;		// from CA::Context::commit_transaction @ 20160428
	x_hash_table* _58;		// roots, from CA::Transaction::commit @ 20160503
	__CFRunLoop* _60;		// runloop, from CA::Transaction::ensure_implicit @ 20160503
	__CFRunLoopObserver* _68;		// runloopObserver, from CA::Transaction::ensure_implicit @ 20160503
	struct slist { void* val; slist* next; }*_70;		// from set_layout_needed(trans), free_transaction
	x_list* _78;		// from CA::Transaction::run_deferred_visibility_layer_calls @ 20160520
	unsigned int _80;		// from CA::Transaction::commit @21060518
	unsigned int _84;		// from CA::Transaction::commit @21060518
	char _88[0];			// buffer, may be the inline Shared, pointed by this->_0, from CA::Transaction::commit @21060518

	
	static void add_command(int, unsigned int, unsigned long, void const*);
	void add_commit_handler(block_pointer/**void() block_pointer*/, CATransactionPhase);
	void add_deferred_visibility_layer(CA::Layer*);
	void add_deleted_id(unsigned long, unsigned int);
	void add_root(CA::Layer*);
	void assert_inactive();
	void begin_transaction();
	static void cf_release(void const*);
	void commit();
	static void commit_transaction();
	CA::Transaction* create();
	Continuation* current_continuation() const;
	unsigned int current_state();
	static Transaction* ensure();
	static Transaction* ensure_compat();
	void ensure_implicit();
	void flush();
	void flush_transaction();
	void foreach_command(unsigned int, void(*)(int, unsigned long, void const*, void*), void*);
	void foreach_deleted_id(void(*)(unsigned long, unsigned int, void*), void*);
	void foreach_root(void(*)(CA::Layer*, void*), void*);
	void free_command_list(Command*);
	Transaction* get();
	bool get_animator(block_pointer&/**void() block_pointer&*/) const;
	bool get_value(unsigned int, _CAValueType, void*);
	void init();
	void lock();
	static void observer_callback(__CFRunLoopObserver*, unsigned long, void*);
	void pop();
	void pop_animator();
	void push();
	void push_animator(/**void() block_pointer*/block_pointer);
	void release_object(void const*);
	void release_thread(void*);
	void remove_root(CA::Layer*);
	void reset_animators();
	void run_commit_handlers(CATransactionPhase);
	void run_deferred_visibility_layer_calls();
	void set_continuation(/**void() block_pointer*/block_pointer);
	void set_fence(unsigned int, unsigned int, unsigned int);
	void set_fence(unsigned int, unsigned int, /**void() block_pointer*/block_pointer);
	void set_value(unsigned int, _CAValueType, void const*);
	void unlock();

};
struct CA::Transaction::Command
{
	Command* _0;				// next, from CA::Transaction::add_command @ 20160503
};
struct CA::Transaction::Continuation
{
	int _0;					// refcnt, from CA::Transaction::set_continuation @ 20160520
	Continuation* _8;		// next, from CA::Transaction::set_continuation @ 20160520
	block_pointer* _10;		// Block, from CA::Transaction::set_continuation @ 20160520
	ref();
	unref();
	~Continuation();

};
struct CA::Transaction::Fence
{
	Fence* _0;			// next, from CA::Context::commit_transaction @ 20160428
	mach_port _8;		// from CA::Transaction::set_fence @ 20160520
	unsigned int _c;	// from CA::Context::commit_transaction @ 20160428
	unsigned int _10;	// from CA::Context::commit_transaction @ 20160428
	mach_port _14;		// from CA::Transaction::set_fence @ 20160520
	x_list* _18;		// from CA::Transaction::set_fence @ 20160520
	release_port() const;
	run_callbacks() const;
	static mach_port create_port();				// by hand, from CA::Context::create_fence_port
	~Fence();

};
struct CA::Transaction::Join
{
	Join(CA::Transaction*);
	~Join();

};
struct CA::Transaction::Level
{
	Level* _0;								// next, from CA::Transaction::get_value @ 20160519
	Continuation*& _8;						// continuation, from CA::Transaction::set_continuation @ 20160520
	CA::AttrList* _10;						// attr list, from CA::Transaction::get_value @ 20160519
	free_levels(CA::Transaction::Level*);
	~Level();
	Level(Level* other) { _0 = other; }
};
struct CA::Transaction::Shared
{
	int _0;
	x_hash_table* _8;						// same thing as Transaction::_10, from CA::Transaction::commit @ 20160519
	int _10;
	CA::Transaction::Command* _18;			// head, from CA::Transaction::add_command @ 20160503
	x_chain* _20;							// picked up to Transaction::_40, from CA::Transaction::commit @ 20160519.  from add_deleted_id @ 20160517
	CA::Transaction::Fence* _28;			// from CA::Context::commit_transaction @ 20160504
	x_list* _30;							// one of four phases, from add_commit_handler @ 20160517
	x_list* _38;							// one of four phases, from add_commit_handler @ 20160517
	x_list* _40;							// one of four phases, from add_commit_handler @ 20160517
	x_list* _48;							// one of four phases, from add_commit_handler @ 20160517
	x_heap_struct *_50;				// slab buffer, from CA::Layer::thread_flags @ 20160503
	struct CA_Layer_slist {
		CA::Layer* _0;
		CA_Layer_slist* _8;				// next;
	} *_70;
	int _68;			// current state, from CA::Transaction::current_state @ 20160519
	x_hash_table* _78;	// presentation layers, from CA::Layer::presentation_layer @ 20160501
	x_hash_table* _80;	// modelLayers, from CA::Layer::model_layer @ 20160501
	double _88;			// from CA::Layer::layer_being_drawn @ 20160501
	int _110;			// the result of backtrace, the count of backtrace_symbols, from  CA::Transaction::push @ 20160519
	bool has_pool();	// by hand
};
struct CA::Transform
{
	apply_to_point2(double*) const;
	apply_to_point2(float*) const;
	apply_to_point4(double*, long, double const*, long, unsigned long) const;
	apply_to_point4(float*, float const*) const;
	apply_to_point4(float*, long, float const*, long, unsigned long) const;
	concat(CA::SimpleTransform const&);
	concat(CA::Transform const&);
	concat_left(CA::Transform const&);
	get_scale(double*, double*) const;
	get_scale_recip(double*, double*) const;
	get_unmatrix(CA::UnMat4&, bool) const;
	identity();
	invert();
	is_identity() const;
	is_isotropic(double) const;
	operator=(CA::Transform const&);
	operator==(CA::Transform const&) const;
	rotate90();
	scale(double, double, double);
	scale_2d(double);
	scale_2d_right(double);
	set(CA::Mat4<double> const&, bool);
	set(CA::SimpleTransform const&);
	set_2x2();
	set_affine(double const*, bool);
	set_affine(double, double, double, double, double, double);
	set_affine_rectilinear(double, double, double, double);
	set_identity();
	set_scale(double, double, double);
	set_translation(double, double, double);
	set_unmatrix(CA::UnMat4 const&);
	translate(double, double, double);
	translate_right(double, double, double);

};
struct CA::UnMat2
{

};
struct CA::UnMat4
{

};
struct CA::Volume
{
	Union(CA::Volume const&);
	apply_transform(CA::Mat4<double> const&);
	apply_transform(CA::SimpleTransform const&);
	apply_transform(CA::Transform const&);
	get_rect(CA::Rect&) const;

};
struct CA::WindowServer::(anonymous namespace)::OGLDisplay
{

};
struct CA::WindowServer::Display
{
	struct ColorMode;
	struct Mode;
	struct Orientation;
	struct OverscanAdjustment;
	struct SignalType;
	Display(__CFString const*);
	begin_update(CA::Render::Update*);
	benchmark_mode() const;
	clear_logical_bounds();
	clone_scale(CA::WindowServer::Display*);
	clone_update(CA::WindowServer::Display*, CA::Render::Update*, unsigned int&, bool&);
	clones_support_detaching();
	cloning_active();
	color_flush_shape(CA::Render::Update*) const;
	contrast() const;
	convert_logical_orientation(Orientation) const;
	copy_uuid_string(char*, unsigned long);
	create_surface(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	detach_layer(CA::Render::Handle*, int, CA::Render::Texture*, CA::WindowServer::Surface*, CA::Rect const*, CA::Rect const*, unsigned int);
	detached_layers_valid_p(CA::Render::Update*);
	digital_mode_id(unsigned long, unsigned long);
	dirty_update_surface();
	finish_update(CA::Render::Update*, unsigned int);
	foreach_detached_layer(void(*)(CA::Render::Handle*, long, CA::Render::Texture*, void*), void*);
	framebuffer() const;
	framebuffer_id() const;
	grayscale() const;
	hidden_when_mirroring_enabled() const;
	idle();
	ignore_update_p(bool, bool);
	inverse_color() const;
	is_ready();
	logical_orientation() const;
	maximum_brightness() const;
	mirroring_enabled() const;
	mode_height(Mode) const;
	mode_pixel_aspect_ratio(Mode);
	mode_width(Mode) const;
	post_display_changed();
	post_display_changed_callback(double, void*);
	purge_surfaces();
	recycle_surface(CA::WindowServer::Surface*);
	refresh_rate() const;
	release_resources();
	render_display(CA::OGL::Renderer&, CA::Render::Update*);
	render_surface(CA::OGL::Renderer&, CA::WindowServer::Surface*, CA::Render::Update*, CA::Bounds const&, bool);
	round_logical_rect(CA::Rect&);
	set_all_modes(ModeSet const&, Mode, Mode);
	set_allows_virtual_modes(bool);
	set_background_color(unsigned int);
	set_color_mode(ColorMode);
	set_contrast(float);
	set_dynamic_mode_size(unsigned long, unsigned long);
	set_grayscale(bool);
	set_ideal_refresh_rate(float);
	set_inverse_color(bool);
	set_logical_bounds(CA::Bounds const&, bool);
	set_logical_orientation(Orientation);
	set_maximum_brightness(float);
	set_maximum_refresh_rate(float);
	set_minimum_refresh_rate(float);
	set_mirroring_enabled(bool);
	set_mode(Mode);
	set_overscan_adjustment(OverscanAdjustment);
	set_process_id(int);
	set_scale(double);
	set_signal_type(SignalType);
	set_size(CA::Vec2<int> const&, CA::Vec2<int> const&);
	set_tag(unsigned int);
	set_uses_preferred_mode_refresh_rate(bool);
	static_mode_height(Mode);
	static_mode_width(Mode);
	transform() const;
	unconvert_logical_orientation(Orientation) const;
	update_actual_bounds();
	update_cloning_flag();
	update_display_modes(bool);
	update_geometry();
	update_input_time(double);
	will_unblank();
	~Display();

};
struct CA::WindowServer::Display::ColorMode
{

};
struct CA::WindowServer::Display::Mode
{

};
struct CA::WindowServer::Display::Orientation
{

};
struct CA::WindowServer::Display::OverscanAdjustment
{

};
struct CA::WindowServer::Display::SignalType
{

};
struct CA::WindowServer::MemorySurface
{
	MemorySurface(CA::WindowServer::Display*, unsigned int, unsigned int, unsigned int, unsigned char*, unsigned long, void(*)(void const*, void*), void*);
	check_alignment(unsigned long, unsigned long) const;
	lock(unsigned char*&, unsigned long&);
	unlock();
	wrap_buffer(CA::WindowServer::Display*, CA::Render::RenderBuffer*);
	~MemorySurface();

};
struct CA::WindowServer::PurpleDisplay
{
	struct Message;
	PurpleDisplay(unsigned int, bool);
	can_update(double);
	copy_uuid_string(char*, unsigned long);
	displayed_surface();
	finish_update(CA::Render::Update*, unsigned int);
	finished_update();
	is_enabled();
	map_surface();
	needs_backstop_window();
	new_server();
	open(bool);
	openMain();
	openTVOut();
	refresh_rate() const;
	release_server();
	send_msg(Message*, bool);
	set_enabled(bool);
	transform() const;
	unmap_surface();
	update_display_modes(bool);
	update_surface(bool, bool);
	update_surface_has_alpha();
	~PurpleDisplay();

};
struct CA::WindowServer::PurpleDisplay::Message
{

};
struct CA::WindowServer::Server
{
	struct PendingOrderAbove;
	struct PendingOrderLevel;
	Server(CA::WindowServer::Display*, __CFString const*);
	add_clone(CA::WindowServer::Server*, unsigned int);
	add_context(CA::Render::Context*);
	add_observers(CA::Render::Context*);
	attach_contexts();
	clear_replay_contexts();
	clone_supports_detaching() const;
	clones() const;
	compare_levels(void const*, void const*);
	context_changed(CA::Render::Object*, void*, void*);
	context_created(CA::Render::Object*, void*, void*);
	context_deleted(CA::Render::Object*, void*, void*);
	context_insert(unsigned long, CA::Render::Context*, float);
	context_ordered(CA::Render::Object*, void*, void*);
	copy_uuid_string(char*, unsigned long) const;
	create_blank_context();
	current_surface();
	debug_changed(__CFNotificationCenter*, void*, __CFString const*, void const*, __CFDictionary const*);
	defer_update(CA::Render::Object*, void*, void*);
	delete_context(CA::Render::Context*);
	destroy_blank_context();
	display_changed(CA::Render::Object*, void*, void*);
	get_debug_log(CA::Render::Object*, void*, void*);
	get_display_info(CA::Render::Object*, void*, void*);
	get_displays(CA::Render::Object*, void*, void*);
	hit_test(CA::Vec2<double> const&);
	immediate_render();
	immediate_render_ready() const;
	implicit_renderer_flags() const;
	invalidate(CA::Shape const*);
	invalidate_context(CA::Render::Context*);
	last_render_time() const;
	order_above(CA::Render::Context*, unsigned long, bool);
	order_level(CA::Render::Context*, float);
	ping_server(CA::Render::Object*, void*, void*);
	purge_resources();
	purge_server(CA::Render::Object*, void*, void*);
	release_resources();
	remove_clone(CA::WindowServer::Server*);
	remove_observers(CA::Render::Context*);
	remove_pending_operations(CA::Render::Context*);
	render_context_layer(CA::Render::Object*, void*, void*);
	render_context_list(CA::Render::Object*, void*, void*);
	render_display(CA::Render::Object*, void*, void*);
	render_display_context_list(CA::Render::Object*, void*, void*);
	render_display_layer(CA::Render::Object*, void*, void*);
	render_for_time(double, CVTimeStamp const*);
	render_surface(CA::Render::Update*, CA::WindowServer::Surface*, CA::Bounds const&, bool);
	render_update(CA::Render::Update*, unsigned int&);
	retain_context(unsigned int);
	run_loop();
	run_pending_operations();
	set_allows_virtual_modes(bool);
	set_blanked(bool);
	set_color_mode(CA::WindowServer::Display::ColorMode);
	set_contrast(float);
	set_display_allows_virtual_modes(CA::Render::Object*, void*, void*);
	set_display_color_mode(CA::Render::Object*, void*, void*);
	set_display_mode(CA::Render::Object*, void*, void*);
	set_display_overscan_adjustment(CA::Render::Object*, void*, void*);
	set_enabled(bool);
	set_grayscale(bool);
	set_ideal_refresh_rate(float);
	set_inverse_color(bool);
	set_maximum_brightness(float);
	set_maximum_refresh_rate(float);
	set_minimum_refresh_rate(float);
	set_mirroring_enabled(bool);
	set_next_update(double, double);
	set_overscan_amounts(CA::Vec2<float> const&);
	set_replay_context_ids(std::__1::vector<unsigned int, std::__1::allocator<unsigned int> > const&);
	set_scale(double);
	set_secure(bool);
	set_uses_preferred_mode_refresh_rate(bool);
	shutdown();
	sw_renderer();
	timer_callback(double, void*);
	update_delay() const;
	update_display_modes(bool);
	will_unblank();
	~Server();

};
struct CA::WindowServer::Server::PendingOrderAbove
{
	run(CA::WindowServer::Server*);
	~PendingOrderAbove();

};
struct CA::WindowServer::Server::PendingOrderLevel
{
	run(CA::WindowServer::Server*);
	~PendingOrderLevel();

};
struct CA::WindowServer::Surface
{
	Surface(CA::WindowServer::Display*, unsigned int, unsigned int, unsigned int);
	change_tiled(bool);
	clear_region(CA::Shape const*, unsigned int);
	color_space() const;
	lock(unsigned char*&, unsigned long&);
	set_color_space(unsigned int);
	set_info(void*, void(*)(CA::WindowServer::Surface*, void*));
	unlock();
	unref();
	~Surface();

};
struct CAImageQueueBuffer
{
	type() const;
	~CAImageQueueBuffer();

};
struct CAImageQueueCommit
{
	CAImageQueueCommit(_CAImageQueue*, CA::GenericContext*);
	~CAImageQueueCommit();

};
struct CAML::Context
{
	struct Object;
	Context();
	add_entity(char const*, _xmlEntity*);
	create_sax_vtable();
	did_load_resource(__CFURL const*, void const*);
	end_script(char*, unsigned long);
	error(char const*, ...);
	errorv(char const*, __va_list_tag*);
	failed_to_load_resource(__CFURL const*);
	finished();
	free_object(__CFString const*, Object*, void*);
	object(__CFString const*, CAML::Type const**) const;
	parse_colorspace_attribute(char const**);
	parse_src_attribute(char const**);
	pop_state();
	push(char const*, unsigned long);
	push_state(CAML::StateName, unsigned int, CAML::Type const*, void(*)(CAML::Context*, CAML::State*));
	result();
	set_base_url(__CFURL const*);
	set_current_url(__CFURL const*);
	set_error(__CFError*);
	set_object(__CFString const*, CAML::Type const*, void const*);
	set_result(void const*);
	start_script(char const**);
	warning(char const*, ...);
	warningv(char const*, __va_list_tag*);
	will_load_resource(__CFURL const*);
	~Context();

};
struct CAML::Context::Object
{
	set(CAML::Type const*, void const*);

};
struct CAML::ObjCBool
{
	ObjCBool();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCBool();

};
struct CAML::ObjCCAColorMatrix
{
	ObjCCAColorMatrix();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCAColorMatrix();

};
struct CAML::ObjCCAPoint3D
{
	ObjCCAPoint3D();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCAPoint3D();

};
struct CAML::ObjCCATransform3D
{
	ObjCCATransform3D();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCATransform3D();

};
struct CAML::ObjCCGAffineTransform
{
	ObjCCGAffineTransform();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCGAffineTransform();

};
struct CAML::ObjCCGColor
{
	ObjCCGColor();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	start(CAML::Context*, CAML::State*, char const**) const;
	~ObjCCGColor();

};
struct CAML::ObjCCGFont
{
	ObjCCGFont();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCGFont();

};
struct CAML::ObjCCGImage
{
	ObjCCGImage();
	start(CAML::Context*, CAML::State*, char const**) const;
	~ObjCCGImage();

};
struct CAML::ObjCCGPDFDocument
{
	ObjCCGPDFDocument();
	start(CAML::Context*, CAML::State*, char const**) const;
	~ObjCCGPDFDocument();

};
struct CAML::ObjCCGPath
{
	ObjCCGPath();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCGPath();

};
struct CAML::ObjCCGPoint
{
	ObjCCGPoint();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCGPoint();

};
struct CAML::ObjCCGRect
{
	ObjCCGRect();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCGRect();

};
struct CAML::ObjCCGSize
{
	ObjCCGSize();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCCGSize();

};
struct CAML::ObjCContext
{
	ObjCContext(CAMLParser*);
	check_type(CAML::Type const*, CAML::Type const*);
	create_builtin_types();
	did_load_resource(__CFURL const*, void const*);
	end_script(char*, unsigned long);
	errorv(char const*, __va_list_tag*);
	eval_script(NSString*, NSURL*, unsigned int);
	failed_to_load_resource(__CFURL const*);
	finished();
	lookup_type(char const*);
	set_delegate(objc_object*);
	start_script(char const**);
	warningv(char const*, __va_list_tag*);
	will_load_resource(__CFURL const*);
	~ObjCContext();

};
struct CAML::ObjCInteger
{
	ObjCInteger();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	is_numeric() const;
	~ObjCInteger();

};
struct CAML::ObjCNSArray
{
	ObjCNSArray();
	start(CAML::Context*, CAML::State*, char const**) const;
	~ObjCNSArray();

};
struct CAML::ObjCNSDictionary
{
	ObjCNSDictionary();
	start(CAML::Context*, CAML::State*, char const**) const;
	~ObjCNSDictionary();

};
struct CAML::ObjCNSObject
{
	ObjCNSObject(char const*, objc_class*);
	builtin_type() const;
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	property_type(CAML::Context*, void const*, unsigned int) const;
	set_property(CAML::Context*, void const*, unsigned int, void const*) const;
	start(CAML::Context*, CAML::State*, char const**) const;
	~ObjCNSObject();

};
struct CAML::ObjCNSSet
{
	ObjCNSSet();
	start(CAML::Context*, CAML::State*, char const**) const;
	~ObjCNSSet();

};
struct CAML::ObjCNSURL
{
	ObjCNSURL();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCNSURL();

};
struct CAML::ObjCNull
{
	ObjCNull();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCNull();

};
struct CAML::ObjCReal
{
	ObjCReal();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	is_numeric() const;
	~ObjCReal();

};
struct CAML::ObjCScript
{
	ObjCScript();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCScript();

};
struct CAML::ObjCString
{
	ObjCString();
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	~ObjCString();

};
struct CAML::ObjCType
{
	builtin_type() const;
	set_property(CAML::Context*, void const*, unsigned int, void const*) const;

};
struct CAML::State
{
	State(CAML::Context*, CAML::StateName, unsigned int, CAML::Type const*, void(*)(CAML::Context*, CAML::State*));
	characters(char const*, int);
	finish();
	property_type(unsigned int);
	set_value(void const*);
	start(char const**);
	~State();

};
struct CAML::StateName
{

};
struct CAML::Type
{
	Type(char const*);
	end(CAML::Context*, CAML::State*, char*, unsigned long) const;
	is_numeric() const;
	property_type(CAML::Context*, void const*, unsigned int) const;
	set_property(CAML::Context*, void const*, unsigned int, void const*) const;
	start(CAML::Context*, CAML::State*, char const**) const;
	~Type();

};
struct CubeTransition::State
{

};
struct FlipTransition::State
{

};
struct RotateTransition::State
{

};

namespace CA
{
	namespace Render
	{
		add_filter(unsigned int, FilterSubclass const*);
		add_observer(NotificationName, Object*, void(*)(Object*, void*, void*), void*, bool);
		add_transition(unsigned int, TransitionSubclass const*);
		void* aligned_calloc(unsigned long, void**);
		void* aligned_copy_data_provider(void const*, void*);
		void aligned_free(void const*, void*);
		aligned_malloc(unsigned long, void**);
		void aligned_protect(void const*, void*);
		aligned_release(void*, void const*, unsigned long);
		aligned_size(void const*, void*);
		alignment_property(AlignmentProperty);
		alloc_occlusion_data(occlusion_closure*, unsigned int);
		animation_get_function_param(unsigned int, unsigned int const*, unsigned long, void*);
		cell_atom_param_index(unsigned int);
		cgimage_is_compressed_texture(CGImage*);
		check_memory_warning(double);
		clip_area(CA::Rect const&, CA::Shape const*);
		clip_layer(LayerNode*, double*, double*, double*);
		collect(double, bool);
		collect_images(double);
		collect_insecure_process_ids(unsigned int, Context*, void*);
		collect_secure_mode_violations(unsigned int, Context*, void*);
		compute_angles(Spline&, CA::Vec2<double> const&, CA::Vec2<double> const&);
		compute_corner_matrix(CA::Mat4<double>&, CA::Vec2<double> const*, CA::Vec2<double> const&, CA::Vec2<double> const&);
		compute_gravity_transform(LayerGravity, CA::Rect const&, CA::Vec2<double> const&, CA::Vec2<double>&, CA::Vec2<double>&);
		compute_occlusion_data(occlusion_closure*, LayerNode*);
		convert_cgcolor(CGColor*, CGColorSpace*, unsigned int&, Pattern**);
		copy_elements(void*, CGPathElement const*);
		copy_image(CGImage*, CGColorSpace*, unsigned int, double);
		copy_render_array(__CFArray const*, Type);
		copy_render_array(__CFArray const*, CGColorSpace* (*)());
		copy_render_value(void const*);
		copy_render_value(void const*, CGColorSpace* (*)());
		count_elements(void*, CGPathElement const*);
		create_image(CGImage*, CGColorSpace*, unsigned int);
		create_pattern_image(CGPattern*, CGColorSpace*, CA::Vec2<double> const&, CGRect const&);
		decode_commands(Decoder*);
		dispose_reply_port(unsigned int, int);
		distance_to_object(Object const*, Object const*);
		emitter_atom_param_index(unsigned int, unsigned long&);
		emitter_behaviors_copy(TypedArray<EmitterBehavior>*);
		emitter_cells_copy(TypedArray<EmitterCell>*);
		emitter_find_behavior(TypedArray<EmitterBehavior>*, unsigned int);
		emitter_find_cell(TypedArray<EmitterCell>*, unsigned int);
		encode_add_animation(Encoder*, unsigned long, Animation*);
		encode_add_input_time(Encoder*, double);
		encode_delete_object(Encoder*, unsigned long, unsigned int);
		encode_delete_slot(Encoder*, unsigned int);
		encode_dictionary_item(void const*, void const*, void*);
		encode_flush_image_queue(Encoder*, unsigned long);
		encode_image_provider_create(Encoder*, unsigned long, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool, float, int, unsigned int, Pattern*);
		encode_image_provider_invalidate(Encoder*, unsigned long, int, int, int, int, unsigned int, unsigned int);
		encode_image_provider_set_fill_color(Encoder*, unsigned long, unsigned int, Pattern*);
		encode_image_provider_set_image_size(Encoder*, unsigned long, unsigned int, unsigned int);
		encode_image_provider_set_max_tile_scale(Encoder*, unsigned long, int);
		encode_image_provider_set_subimage(Encoder*, unsigned long, unsigned int, unsigned int, unsigned int, Texture*, unsigned int, unsigned int);
		encode_invalidation(Object const*, unsigned int, void*);
		encode_object_is_volatile(Encoder*, unsigned long, unsigned int);
		encode_order_level(Encoder*, float);
		encode_order_relative(Encoder*, bool, unsigned int);
		encode_remove_all_animations(Encoder*, unsigned long);
		encode_remove_animation(Encoder*, unsigned long, __CFString const*);
		encode_set_layer_id(Encoder*, unsigned long);
		encode_set_low_latency(Encoder*);
		encode_set_object(Encoder*, unsigned long, unsigned int, Object*, unsigned int);
		encode_set_slot(Encoder*, unsigned int, Object*);
		encode_update_layer(Encoder*, unsigned long);
		encode_volatile(Object const*, unsigned int, void*);
		find_port(unsigned int, Context*, void*);
		float_color(unsigned int, double*, bool);
		float_color(unsigned int, float*, bool);
		flush_images();
		format_Bpp(unsigned int);
		int format_bitmap_info(unsigned int);
		int format_bpc(unsigned int);
		int format_bpp(unsigned int);
		format_default_colorspace(unsigned int);
		format_has_alpha(unsigned int);
		format_is_floating_point(unsigned int);
		format_is_native(unsigned int);
		format_mipmap_min_size(unsigned int);
		format_name(unsigned int);
		format_opaque_format(unsigned int);
		format_pixel_format_type(unsigned int);
		unsigned long format_rowbytes(unsigned int, unsigned int);
		free_entry(Image*, TileCacheEntry*, void*);
		free_subimage(ImageProviderKey*, ImageProviderSubImage*, void*);
		get_affine_property(Vector*, int, unsigned int const*, double*);
		get_point_property(CA::Vec2<double> const&, int, unsigned int const*, double*);
		get_rect_property(CA::Rect const&, int, unsigned int const*, double*);
		get_reply_port();
		get_size_property(CA::Vec2<double> const&, int, unsigned int const*, double*);
		get_transform_property(Vector*, int, unsigned int const*, double*);
		unsigned long image_data_size(unsigned long, unsigned int);
		image_format_for_astc(int, int);
		in_both_half_spaces(occlusion_data*, occlusion_data*, double);
		init_memory_warnings_(void*);
		initialize_memory_warnings();
		insert_node_by_minz(x_link_struct*, LayerNode*);
		invalidate_animation(Handle*, Animation*);
		invalidate_callback(ImageProviderKey*, ImageProviderSubImage*, void*);
		invalidate_context(Context*);
		key_compare(ImageProviderKey*, ImageProviderKey*);
		key_hash(ImageProviderKey*);
		key_path_atom(void* const*, unsigned long);
		key_path_atoms(void* const*, unsigned int*);
		key_path_copy(void**, void* const*);
		key_path_copy_string(void* const*);
		key_path_count(void* const*);
		key_path_equal(void* const*, void* const*, bool);
		key_path_free(void**);
		key_path_set(void**, __CFString const*);
		key_path_set_atom(void**, unsigned int);
		key_path_set_atoms(void**, unsigned long, unsigned int const*);
		layer_apply(Layer*, float, double, double);
		make_splines(Path*, Spline*, unsigned long);
		memory_warning(void*);
		mix_objects(Object*, Object*, Object*, Object*, ValueInterpolator const&);
		mix_objects(Object*, Object*, ValueInterpolator const&);
		mix_splines(Spline*, Spline*, Spline*, int, int, float);
		morph_paths(Path*, Path*, float);
		next_cache_id();
		next_sequence();
		parse_index(char const*, char const*);
		pattern_deleted(CGNotificationCenter*, void*, __CFString const*, void const*, __CFDictionary const*);
		pixel_color(double const*);
		pixel_color_premul(double const*);
		pixel_color_premul(float const*);
		pixel_format_type_format(unsigned int);
		pixel_format_type_has_alpha(unsigned int);
		point_inside_layer(CA::Vec2<double> const*, CA::Vec2<double> const&, CA::Vec2<double> const&, CA::Vec2<double>&);
		point_interpolate(double*, double const*, double const*, double, double, double);
		post_notification(NotificationName, Object*, void*, bool);
		prepare_image(CGImage*, CGColorSpace*, unsigned int, double);
		prepare_render_value(void const*, CGColorSpace* (*)());
		print_flags(unsigned int, char const**, unsigned long);
		releaseCFData(void const*, void*);
		release_bitmap(void*, void const*, unsigned long);
		release_cfdata(void const*, void*);
		release_cvpixelbuffer(void const*, void*);
		release_deallocate(void const*, void*);
		release_free(void const*, void*);
		release_image_data(void const*, void*);
		release_object(void const*, void*);
		release_provider(void*, void const*, unsigned long);
		release_shmem_bitmap(void const*, void*);
		remove_every_observer(void*);
		remove_observer(NotificationName, Object*, void(*)(Object*, void*, void*), void*);
		render_image_deleted(Object*, void*, void*);
		separating_axis(occlusion_data const*, occlusion_data const*, unsigned int, unsigned int, double);
		set_affine_property(Vector*, int, unsigned int const*, bool, unsigned long, double const*);
		set_minimum_alignment(unsigned long);
		set_point_property(CA::Vec2<double>&, int, unsigned int const*, bool, unsigned long, double const*);
		set_rect_property(CA::Rect&, int, unsigned int const*, bool, unsigned long, double const*);
		set_rect_vector_property(Vector*, unsigned long, unsigned int const*, bool, unsigned long, double const*);
		set_size_property(CA::Vec2<double>&, int, unsigned int const*, bool, unsigned long, double const*);
		set_transform_property(Vector*, int, unsigned int const*, bool, unsigned long, double const*);
		show_affine_transform(char const*, CGAffineTransform const&, unsigned int);
		show_cfstring(__CFString const*);
		show_image_cache();
		show_newline(unsigned int);
		show_object(Object const*);
		show_object(Object const*, unsigned int, unsigned int);
		show_statistics();
		show_transform(char const*, double const*, unsigned int);
		skip_sublayers(Layer*&, void* const*, int);
		spline_count(Path*);
		tile_cache_entry_release_images(TileCache*, TileCacheEntry*);
		unref_object(void const*, void*);
		update_texture_flags(Texture*, _CAShmemImageQueue*, unsigned int, unsigned int);
		update_z_range_clip(LayerNode*);
		updater_mark_detached_layer(LayerNode*, bool);
	}
}

namespace CA
{
	CA::downsample_image(unsigned int, void const*, unsigned long, unsigned long, unsigned long, void*, unsigned long, double, double, double, double, unsigned int);
}