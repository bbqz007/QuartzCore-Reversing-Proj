# CA.backing.cpp
```
void CABackingStoreCollect_(double curMediaTime, bool flag)

void CABackingStoreCollect(double curMediaTime)

void backing_store_callback(double, void*)

CA::call_at_time(fn_backing_store_callback backing_store_callback, double curMediaTime, void* unknown)

void async_collect_callback(void*)
```

# CA.Context.cpp
```
CA::Context::~Context()

void CA::Context::destroy()

CA::Context::Context(__CFDictionary const* dict)

CA::Context::set_colorspace(CGColorSpace* colorSpace)

bool CA::Context::is_secure()

void CA::Context::invalidate_fences()

void CA::Context::invalidate()

CGColorSpace* CA::Context::current_colorspace(CA::Transaction* transaction)

CA::Context* CA::Context::retain_context_with_client_port(unsigned int client_port)

CA::Context* CA::Context::retain_context_with_id(unsigned int id)

CALayer* CA::Context::retain_layer()

__CFArray* CA::Context::retain_objc_contexts()

CA::Render::Context* CA::Context::retain_render_ctx()

CA::Context** CA::Context::retain_all_contexts(bool flag1, CA::Context** contexts, unsigned long& length)

mach_port CA::Context::client_port()

mach_port CA::Context::create_fence_port()

int32_t CA::Context::new_slot()

int32_t CA::Context::new_image_slot(unsigned int flag1, unsigned int flag2, bool bWhat)

void CA::Context::delete_slot(unsigned int slot)

bool CA::Context::connect_local()

bool CA::Context::connect_remote()

void CA::Context::get_layer_shmem(unsigned long hkey, CA::Render::ShmemPtr<CA::Render::LayerShmem>& shmemPtr)

bool CA::Context::get_layer_renderer_info(unsigned long flag1, unsigned int flag2, _CARenderRendererInfo* info, unsigned long flag3)

bool CA::Context::get_backdrop_layer_statistics(unsigned long flag, double* unknownF)

bool CA::Context::synchronize(unsigned int flag1, int flag2)

void CA::Context::set_objc_context(void const* ctx)
```

# CA.Context+commit.cpp
```
void CA::Context::commit_root(CA::Layer* layer, void* unknownCTX)

double CA::Context::commit_layer_time(CA::Layer* layer, double givenTime, void* unknownCTX)

void CA::Context::commit_layer(CA::Layer* layer, unsigned int flag1, unsigned int flag2, void* unknownCTX)

void CA::Context::commit_deleted(unsigned long hkey, unsigned int id, void* unknownCTX)

void CA::Context::commit_animation(CA::Layer* layer, CA::Render::Animation* anima, void* unknownCTX)

void CA::Context::commit_command(Command command, unsigned long cmd_arg, void const* unknownCTX)
```

# CA.cpp
```
bool CA::Layer::layout_is_active(CA::Transaction* transaction, bool isActive)

void CA::Layer::layout_and_display_if_needed(CA::Transaction* transaction)

void CA::Layer::layout_if_needed(CA::Transaction* transaction)

void CA::Layer::set_needs_layout()

int CA::Layer::add_animation(CAAnimation* anima, __CFString const* key_path)

void CA::Layer::set_animations(CA::Layer::Animation* anima)

bool CA::Layer::collect_animations__(double arg1, double* arg2, CA::Layer::CollectAnimationsData* data)
```

# CA.misc.cpp
```
void CA::Layer::update_sublayers(CA::Transaction* transaction, CALayerArray* oldSublayers, CALayerArray* newSublayers)

void CA::Layer::update_removed_sublayer(CA::Transaction* transaction, unsigned int visibleFlags)

void CA::Layer::update_for_changed_sublayers(CA::Transaction* transaction, unsigned int visibleFlags)

void CA::Layer::update_added_sublayer(CA::Transaction* transaction, CA::Layer* sublayer, unsigned int visibleFlags)

void CA::Layer::toggle_flipped(CA::Transaction* transaction)

CALayer* CA::Layer::superlayer()

CALayerArray* CA::Layer::sublayers()

bool CA::Layer::style_value(unsigned int hkey, objc_object** value)

void CA::Layer::replace_sublayer(CA::Transaction* transaction, CALayer* removeLayer, CALayer* replaceWithLayer)

void CA::Layer::remove_sublayer(CA::Transaction* transaction, CALayer* sublayer)

void CA::Layer::remove_from_superlayer()

void CA::Layer::remove_from_context()

bool CA::Layer::needs_layout()

bool CA::Layer::needs_display()

CALayer* CA::Layer::mask()

void CA::Layer::mark_visible(CA::Transaction* transaction, bool bWhat)

void CA::Layer::mark_sublayers_should_fetch_geometry()

void CA::Layer::mark_context_changed(CA::Transaction* transaction)

void CA::Layer::mark_animations(CA::Transaction* transaction, bool bWhat)

void CA::Layer::mark(CA::Transaction* transaction, unsigned int flag1, unsigned int flag2)

static void CA::Layer::map_geometry(CALayer* fromLayer, CALayer* toLayer, applyVec2r_func applyVec2r, unapplyVec2r_func unapplyVec2r, void* _cvtPoint /**CGPoint{0x8(%rsp) 0x10(%rsp)}*/)

void* CA::Layer::fetch_defaults()

void CA::Layer::add_animation(CAAnimation* anima, __CFString const* keyPath)

void CA::Layer::prepare_commit(CA::Transaction* transaction)

void CA::Layer::prepare_animations(CA::Transaction* transaction)

void CA::Layer::run_animation_callbacks(void*)

void CA::Layer::run_animation_callbacks_compat(double timing, void* objc_obj)

CA::Context* CA::Layer::retain_context()

CA::Layer::State* CA::Layer::writable_state(CA::Transaction* transaction)

CA::Layer::~Layer()

CA::Layer* CA::Layer::model_layer(CA::Transaction* transaction)

CALayer* CA::Layer::presentation_layer(CA::Transaction* transaction)

CALayer* CA::Layer::layer_being_drawn(CA::Transaction* transaction, unsigned int flag)

CALayer* CA::Layer::layer_at_time(CA::Transaction* transaction, double atTime, bool flag1, bool flag2)

CA::Layer::Layer(CALayer* oclayer, State const& inState, State const* outState, CA::Transaction* transaction, unsigned int flag)

void CA::Layer::latch_thread_flags(CA::Transaction* transaction, unsigned int* thread_flags)

bool CA::Layer::is_visible()

void CA::Layer::invalidate_sublayers(CA::Transaction* transaction)

void CA::Layer::invalidate_layout()

void CA::Layer::invalidate_contents()

void CA::Layer::invalidate_animations(CA::Transaction*)

void CA::Layer::insert_sublayer(CA::Transaction* transaction, CALayer* sublayer, unsigned long index)

void CA::Layer::getter(unsigned int hkey, _CAValueType valueType, void* value)

void CA::Layer::get_frame_transform(CGAffineTransform& transform, bool flag)

void CA::Layer::free_transaction(CA::Transaction* transaction)

void CA::Layer::free_animation(Animation* anima, bool dispose)

void CA::Layer::fetch_geometry(CA::Transaction* transaction)

int CA::Layer::fetch_defaults()

void CA::Layer::ensure_transaction_recursively(CA::Transaction* transaction)

void CA::Layer::ensure_mipmaps()

void CA::Layer::end_change(CA::Transaction* transaction, unsigned int atom, objc_object* voucher)

void CA::Layer::did_commit(CA::Transaction* transaction)

void CA::Layer::default_value(unsigned int hkey, _CAValueType valueType, void* value)

CA::Render::Layer* CA::Layer::copy_render_layer(CA::Transaction* transaction, unsigned int layerFlags, unsigned int* commitFlags)

bool CA::Layer::convert_time(CA::Transaction* transaction, double& want_to_convert_time, CALayer* from, CALayer* to)

void CA::Layer::contents_visibility_changed(CA::Transaction* transaction, bool isChagned)

void CA::Layer::commit_thread_flags(unsigned int thread_flags)

bool CA::Layer::commit_if_needed(CA::Transaction* transaction,
	void(*commit_layer)(CA::Layer*, unsigned int, unsigned int, void*),
	void* token)

void CA::Layer::commit_animations(CA::Transaction* transaction,
	double(*commit_layer)(CA::Layer*, double, void*),
	void(*commit_animation)(CA::Layer*, CA::Render::Animation*, void*),
	void(*remove_animation)(CA::Layer*, __CFString const*, void*),
	void*)

uintptr_t CA::Layer::animation_heart_beat(CAAnimation*, __CFString const*)

void CA::Layer::animation_visibility_changed(CA::Transaction* transaction, bool visibility)

void CA::Layer::begin_change(CA::Transaction* transaction, unsigned int atom, objc_object*& voucher)

void CA::Layer::call_did_become_visible()

int CA::Layer::changed_flags_for_class(objc_class* cls)

CA::Layer::State* CA::Layer::class_state(objc_class* cls)

void CA::Layer::collect_layers_(CollectLayersData* data)

CA::Layer::collect_non_visible_animations(CA::Transaction* transaction)

void CA::Layer::collect_non_visible_callback(void const* elem, void* context)
```

# CA.property.cpp
```
void CA::Layer::property_did_change(CA::Transaction* transaction, unsigned int flag)
```

# CA.Render.Encoder.cpp
```
CA::Render::Encoder::Encoder(x_heap_struct* heap, unsigned int flag1, void* something, unsigned int flag2, double flt)

void CA::Render::Encoder::encode_port(unsigned int port1, unsigned int port2, bool bWhat)

void CA::Render::Encoder::encode_object_uncached(CA::Render::Object const* uncachedObject)

void CA::Render::Encoder::encode_object(CA::Render::Object const* rndrObject)

void CA::Render::Encoder::encode_atom(unsigned int atom)

void CA::Render::Encoder::encode_cfobject(void const* cfobject)

void CA::Render::Encoder::encode_data_async(void const* dataObject, unsigned long dataLength, void(*release_cfdata)(void const*, void*), void* context)

void CA::Render::Encoder::receive_reply(unsigned int reply_port)

void CA::Render::Encoder::send_message(unsigned int send_port, unsigned int reply_port)
```

















