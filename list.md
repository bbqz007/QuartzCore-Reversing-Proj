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

# CA.misc.cpp
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

# CA.Render.Encoder.cpp
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

# CA.Render.Object.cpp
```
CA::Render::Object::Object(CA::Render::Decoder* decoder, unsigned int flag)

bool CA::Render::Object::caches_encoding()

bool CA::Render::Object::can_mix_with_object(CA::Render::Object*)

CA::Render::Object* CA::Render::Object::external_ref() const

bool CA::Render::Object::external_unref() const

void CA::Render::Object::finalize()

uintptr_t CA::Render::Object::ogl_image_key() const

CA::Render::Object* CA::Render::Object::ref() const

int64_t CA::Render::Object::refcount() const

int CA::Render::Object::show(unsigned int flag1, unsigned int flag2) const

```

# CA.Render.Shmem.cpp
```
void* CA::Render::Shmem::copy_image(CGColorSpace* colorSpace)

CGImage* CA::Render::Shmem::copy_cgimage(CGColorSpace* colorSpace)

bool CA::Render::Shmem::set_volatile(bool bVolatile, int flag)

CA::Render::Shmem* CA::Render::Shmem::decode(CA::Render::Decoder* decoder)

CA::Render::Shmem* CA::Render::Shmem::encode(CA::Render::Encoder* encoder) const

bool CA::Render::Shmem::is_purged() const

bool CA::Render::Shmem::is_volatile() const

CA::Render::ShmemBitmap CA::Render::Shmem::new_bitmap(unsigned int arg1, unsigned int width, unsigned int height, unsigned int scale)

CA::Render::Shmem* CA::Render::Shmem::new_shmem(unsigned long size)

mach_port CA::Render::Shmem::port() const

```

# CA.Render.ShmemBitmap.cpp
```
void CA::Render::ShmemBitmap::copy_pixels(CA::Render::ShmemBitmap const* other, CGSRegionObject* region)


```

# CA.Transaction.cpp
```
void CA::Transaction::unlock()

void CA::Transaction::set_value(unsigned int hkey, _CAValueType valueType, void const* value)

void CA::Transaction::set_fence(unsigned int port1, unsigned int port2, block_pointer Block)

void CA::Transaction::set_continuation(block_pointer Block)

void CA::Transaction::run_deferred_visibility_layer_calls()

void CA::Transaction::run_commit_handlers(CATransactionPhase phase)

void CA::Transaction::reset_animators()

void CA::Transaction::remove_root(CA::Layer* root)

void CA::Transaction::release_thread(void* thread)

void CA::Transaction::release_object(void const* obj)

void CA::Transaction::push_animator(block_pointer Block)

void CA::Transaction::push()

void CA::Transaction::pop_animator()

void CA::Transaction::pop()

void CA::Transaction::lock()

void CA::Transaction::init()

bool CA::Transaction::get_value(unsigned int hkey, _CAValueType valueType, void* value)

bool CA::Transaction::get_animator(block_pointer& Block) const

void CA::Transaction::free_command_list(Command* command)

void CA::Transaction::foreach_root(void(*commit_root)(CA::Layer*, void*), void* context)

void CA::Transaction::foreach_deleted_id(void(*commit_deleted)(unsigned long, unsigned int, void*), void* context)

void CA::Transaction::foreach_command(unsigned int flag, void(*commit_command)(int, unsigned long, void const*, void*), void* context)

void CA::Transaction::flush_transaction()

void CA::Transaction::flush()

unsigned int CA::Transaction::current_state()

void CA::Transaction::commit_transaction()

void CA::Transaction::commit()

void CA::Transaction::cf_release(void const* cf_obj)

void CA::Transaction::begin_transaction()

void CA::Transaction::assert_inactive()

void CA::Transaction::add_root(CA::Layer* rootLayer)

void CA::Transaction::add_deleted_id(unsigned long hobj, unsigned int id)

void CA::Transaction::add_deferred_visibility_layer(CA::Layer* deferredLayer)

void CA::Transaction::add_commit_handler(block_pointer Block, CATransactionPhase phase)

CA::Transaction* CA::Transaction::ensure()

CA::Transaction* CA::Transaction::ensure_compat()

void CA::Transaction::ensure_implicit()

CA::Transaction* CA::Transaction::create()

void CA::Transaction::add_command(int arg1, unsigned int arg2, unsigned long arg3, void const* arg4)



```

# CA+display.cpp
```
bool CA::Layer::display_if_needed(CA::Transaction* transaction)

void CA::Layer::display()

void ___ZN2CA5Layer8display_Ev_block_invoke(_NSConcreteBlock* Block)

```

# CA+setter.cpp
```
void CA::Layer::set_visible(unsigned int visibleFlags)

void CA::Layer::set_position(CA::Vec2<double> const& position, bool bAnima)

void CA::Layer::set_next_animation_time(CA::Transaction* transaction, double nextTime1, double nextTime2)

void CA::Layer::set_needs_layout()

void CA::Layer::set_needs_display_in_rect(CGRect const& rect)

uint32_t* CA::Layer::thread_flags_(CA::Transaction* transaction)

void CA::Layer::set_model_layer(CA::Transaction* transaction, CA::Layer* modelLayer)

void CA::Layer::set_mask(CALayer* maskLayer)

void CA::Layer::set_bit_int(unsigned int flag1, unsigned int flag2, unsigned int flag3, unsigned int flag4, unsigned int flag5)

void CA::Layer::set_bit(unsigned int flag1, unsigned int flag2, unsigned int flag3, bool bWhat, void(CA::Layer::*callback)(CA::Transaction*))

void CA::Layer::set_animations(Animation* anima)

void CA::Layer::set_commit_needed(CA::Transaction* transaction, unsigned int flag)

void CA::Layer::set_bounds(CA::Rect const& rect, bool anim)

void CA::Layer::set_delegate(objc_object* delegate)

void CA::Layer::set_sublayers(__CFArray const* sublayers)

void CA::Layer::setter(unsigned int hkey, _CAValueType type, void const* value)

```

# CABackingStoreUpdate_.cpp
```
void CABackingStoreUpdate_(CABackingStore* content, unsigned int width, unsigned int height, unsigned int flag1, unsigned int flag2,  void(*backing_callback)(CGContext*, void*), CA::Layer* layer, CA::GenericContext* context)

```

# transaction.commit_tr~.cpp
```
void CA::Context::commit_transaction(CA::Transaction* transaction)
```

# UIKit.UIView.cpp
```
+[UIView(Animation) beginAnimations:context:]

+[UIViewAnimationState pushViewAnimationState:context:]

+[UIView(UIViewAnimationWithBlocks) _setupAnimationWithDuration:delay:view:options:animations:start:completion:]

```

# UIView+Rendering.cpp
```
+[UIView(Rendering) flush]

+[UIView(Internal) _transitionFromView:toView:duration:options:animations:completion:]

+[UIView(UIViewAnimationWithBlocks) _setupAnimationWithDuration:delay:view:options:factory:animations:start:animationStateGenerator:completion:]


```

# x_log.cpp
```
void x_logv(int handle, const char* fmt, va_list_t* va_list)

```










