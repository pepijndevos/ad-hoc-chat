// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Message.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace MessageProto {
class MessageDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<Message> {
} _Message_default_instance_;

namespace protobuf_Message_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, seq_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, msg_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, sender_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, flags_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, checksum_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, payload_),
  3,
  4,
  0,
  ~0u,
  1,
  2,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 10, sizeof(Message)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Message_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "Message.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void TableStruct::Shutdown() {
  _Message_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _Message_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\rMessage.proto\022\014MessageProto\"\305\001\n\007Messag"
      "e\022\013\n\003seq\030\001 \001(\005\022\016\n\006msg_id\030\002 \001(\005\022\021\n\tsender"
      "_id\030\003 \001(\t\022*\n\005flags\030\004 \003(\0162\033.MessageProto."
      "Message.Flags\022\020\n\010checksum\030\020 \001(\t\022\017\n\007paylo"
      "ad\030\021 \001(\t\";\n\005Flags\022\r\n\tCONNECTED\020\000\022\n\n\006LEAD"
      "ER\020\001\022\010\n\004VOTE\020\002\022\r\n\tCANDIDATE\020\003"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 229);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Message.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_Message_2eproto

const ::google::protobuf::EnumDescriptor* Message_Flags_descriptor() {
  protobuf_Message_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_Message_2eproto::file_level_enum_descriptors[0];
}
bool Message_Flags_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const Message_Flags Message::CONNECTED;
const Message_Flags Message::LEADER;
const Message_Flags Message::VOTE;
const Message_Flags Message::CANDIDATE;
const Message_Flags Message::Flags_MIN;
const Message_Flags Message::Flags_MAX;
const int Message::Flags_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Message::kSeqFieldNumber;
const int Message::kMsgIdFieldNumber;
const int Message::kSenderIdFieldNumber;
const int Message::kFlagsFieldNumber;
const int Message::kChecksumFieldNumber;
const int Message::kPayloadFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Message::Message()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_Message_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:MessageProto.Message)
}
Message::Message(const Message& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      flags_(from.flags_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  sender_id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_sender_id()) {
    sender_id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.sender_id_);
  }
  checksum_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_checksum()) {
    checksum_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.checksum_);
  }
  payload_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_payload()) {
    payload_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.payload_);
  }
  ::memcpy(&seq_, &from.seq_,
    reinterpret_cast<char*>(&msg_id_) -
    reinterpret_cast<char*>(&seq_) + sizeof(msg_id_));
  // @@protoc_insertion_point(copy_constructor:MessageProto.Message)
}

void Message::SharedCtor() {
  _cached_size_ = 0;
  sender_id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  checksum_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  payload_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&seq_, 0, reinterpret_cast<char*>(&msg_id_) -
    reinterpret_cast<char*>(&seq_) + sizeof(msg_id_));
}

Message::~Message() {
  // @@protoc_insertion_point(destructor:MessageProto.Message)
  SharedDtor();
}

void Message::SharedDtor() {
  sender_id_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  checksum_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  payload_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void Message::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Message::descriptor() {
  protobuf_Message_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_Message_2eproto::file_level_metadata[0].descriptor;
}

const Message& Message::default_instance() {
  protobuf_Message_2eproto::InitDefaults();
  return *internal_default_instance();
}

Message* Message::New(::google::protobuf::Arena* arena) const {
  Message* n = new Message;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Message::Clear() {
// @@protoc_insertion_point(message_clear_start:MessageProto.Message)
  flags_.Clear();
  if (_has_bits_[0 / 32] & 7u) {
    if (has_sender_id()) {
      GOOGLE_DCHECK(!sender_id_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*sender_id_.UnsafeRawStringPointer())->clear();
    }
    if (has_checksum()) {
      GOOGLE_DCHECK(!checksum_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*checksum_.UnsafeRawStringPointer())->clear();
    }
    if (has_payload()) {
      GOOGLE_DCHECK(!payload_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*payload_.UnsafeRawStringPointer())->clear();
    }
  }
  if (_has_bits_[0 / 32] & 24u) {
    ::memset(&seq_, 0, reinterpret_cast<char*>(&msg_id_) -
      reinterpret_cast<char*>(&seq_) + sizeof(msg_id_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool Message::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MessageProto.Message)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(16383u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 seq = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u)) {
          set_has_seq();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &seq_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 msg_id = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u)) {
          set_has_msg_id();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &msg_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string sender_id = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sender_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->sender_id().data(), this->sender_id().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "MessageProto.Message.sender_id");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .MessageProto.Message.Flags flags = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::MessageProto::Message_Flags_IsValid(value)) {
            add_flags(static_cast< ::MessageProto::Message_Flags >(value));
          } else {
            mutable_unknown_fields()->AddVarint(4, value);
          }
        } else if (static_cast< ::google::protobuf::uint8>(tag) ==
                   static_cast< ::google::protobuf::uint8>(34u)) {
          DO_((::google::protobuf::internal::WireFormat::ReadPackedEnumPreserveUnknowns(
                 input,
                 4,
                 ::MessageProto::Message_Flags_IsValid,
                 mutable_unknown_fields(),
                 this->mutable_flags())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string checksum = 16;
      case 16: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(130u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_checksum()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->checksum().data(), this->checksum().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "MessageProto.Message.checksum");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string payload = 17;
      case 17: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(138u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_payload()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->payload().data(), this->payload().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "MessageProto.Message.payload");
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MessageProto.Message)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MessageProto.Message)
  return false;
#undef DO_
}

void Message::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MessageProto.Message)
  // optional int32 seq = 1;
  if (has_seq()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->seq(), output);
  }

  // optional int32 msg_id = 2;
  if (has_msg_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->msg_id(), output);
  }

  // optional string sender_id = 3;
  if (has_sender_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->sender_id().data(), this->sender_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MessageProto.Message.sender_id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->sender_id(), output);
  }

  // repeated .MessageProto.Message.Flags flags = 4;
  for (int i = 0, n = this->flags_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->flags(i), output);
  }

  // optional string checksum = 16;
  if (has_checksum()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->checksum().data(), this->checksum().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MessageProto.Message.checksum");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      16, this->checksum(), output);
  }

  // optional string payload = 17;
  if (has_payload()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MessageProto.Message.payload");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      17, this->payload(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MessageProto.Message)
}

::google::protobuf::uint8* Message::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:MessageProto.Message)
  // optional int32 seq = 1;
  if (has_seq()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->seq(), target);
  }

  // optional int32 msg_id = 2;
  if (has_msg_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->msg_id(), target);
  }

  // optional string sender_id = 3;
  if (has_sender_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->sender_id().data(), this->sender_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MessageProto.Message.sender_id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->sender_id(), target);
  }

  // repeated .MessageProto.Message.Flags flags = 4;
  for (int i = 0, n = this->flags_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      4, this->flags(i), target);
  }

  // optional string checksum = 16;
  if (has_checksum()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->checksum().data(), this->checksum().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MessageProto.Message.checksum");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        16, this->checksum(), target);
  }

  // optional string payload = 17;
  if (has_payload()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MessageProto.Message.payload");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        17, this->payload(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MessageProto.Message)
  return target;
}

size_t Message::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MessageProto.Message)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  // repeated .MessageProto.Message.Flags flags = 4;
  {
    size_t data_size = 0;
    unsigned int count = this->flags_size();for (unsigned int i = 0; i < count; i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
        this->flags(i));
    }
    total_size += (1UL * count) + data_size;
  }

  if (_has_bits_[0 / 32] & 31u) {
    // optional string sender_id = 3;
    if (has_sender_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->sender_id());
    }

    // optional string checksum = 16;
    if (has_checksum()) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->checksum());
    }

    // optional string payload = 17;
    if (has_payload()) {
      total_size += 2 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->payload());
    }

    // optional int32 seq = 1;
    if (has_seq()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->seq());
    }

    // optional int32 msg_id = 2;
    if (has_msg_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->msg_id());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Message::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:MessageProto.Message)
  GOOGLE_DCHECK_NE(&from, this);
  const Message* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Message>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:MessageProto.Message)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:MessageProto.Message)
    MergeFrom(*source);
  }
}

void Message::MergeFrom(const Message& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MessageProto.Message)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  flags_.MergeFrom(from.flags_);
  if (from._has_bits_[0 / 32] & 31u) {
    if (from.has_sender_id()) {
      set_has_sender_id();
      sender_id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.sender_id_);
    }
    if (from.has_checksum()) {
      set_has_checksum();
      checksum_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.checksum_);
    }
    if (from.has_payload()) {
      set_has_payload();
      payload_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.payload_);
    }
    if (from.has_seq()) {
      set_seq(from.seq());
    }
    if (from.has_msg_id()) {
      set_msg_id(from.msg_id());
    }
  }
}

void Message::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:MessageProto.Message)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Message::CopyFrom(const Message& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MessageProto.Message)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Message::IsInitialized() const {
  return true;
}

void Message::Swap(Message* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Message::InternalSwap(Message* other) {
  flags_.UnsafeArenaSwap(&other->flags_);
  sender_id_.Swap(&other->sender_id_);
  checksum_.Swap(&other->checksum_);
  payload_.Swap(&other->payload_);
  std::swap(seq_, other->seq_);
  std::swap(msg_id_, other->msg_id_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Message::GetMetadata() const {
  protobuf_Message_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_Message_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Message

// optional int32 seq = 1;
bool Message::has_seq() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void Message::set_has_seq() {
  _has_bits_[0] |= 0x00000008u;
}
void Message::clear_has_seq() {
  _has_bits_[0] &= ~0x00000008u;
}
void Message::clear_seq() {
  seq_ = 0;
  clear_has_seq();
}
::google::protobuf::int32 Message::seq() const {
  // @@protoc_insertion_point(field_get:MessageProto.Message.seq)
  return seq_;
}
void Message::set_seq(::google::protobuf::int32 value) {
  set_has_seq();
  seq_ = value;
  // @@protoc_insertion_point(field_set:MessageProto.Message.seq)
}

// optional int32 msg_id = 2;
bool Message::has_msg_id() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
void Message::set_has_msg_id() {
  _has_bits_[0] |= 0x00000010u;
}
void Message::clear_has_msg_id() {
  _has_bits_[0] &= ~0x00000010u;
}
void Message::clear_msg_id() {
  msg_id_ = 0;
  clear_has_msg_id();
}
::google::protobuf::int32 Message::msg_id() const {
  // @@protoc_insertion_point(field_get:MessageProto.Message.msg_id)
  return msg_id_;
}
void Message::set_msg_id(::google::protobuf::int32 value) {
  set_has_msg_id();
  msg_id_ = value;
  // @@protoc_insertion_point(field_set:MessageProto.Message.msg_id)
}

// optional string sender_id = 3;
bool Message::has_sender_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void Message::set_has_sender_id() {
  _has_bits_[0] |= 0x00000001u;
}
void Message::clear_has_sender_id() {
  _has_bits_[0] &= ~0x00000001u;
}
void Message::clear_sender_id() {
  sender_id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_sender_id();
}
const ::std::string& Message::sender_id() const {
  // @@protoc_insertion_point(field_get:MessageProto.Message.sender_id)
  return sender_id_.GetNoArena();
}
void Message::set_sender_id(const ::std::string& value) {
  set_has_sender_id();
  sender_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessageProto.Message.sender_id)
}
#if LANG_CXX11
void Message::set_sender_id(::std::string&& value) {
  set_has_sender_id();
  sender_id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MessageProto.Message.sender_id)
}
#endif
void Message::set_sender_id(const char* value) {
  set_has_sender_id();
  sender_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessageProto.Message.sender_id)
}
void Message::set_sender_id(const char* value, size_t size) {
  set_has_sender_id();
  sender_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessageProto.Message.sender_id)
}
::std::string* Message::mutable_sender_id() {
  set_has_sender_id();
  // @@protoc_insertion_point(field_mutable:MessageProto.Message.sender_id)
  return sender_id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Message::release_sender_id() {
  // @@protoc_insertion_point(field_release:MessageProto.Message.sender_id)
  clear_has_sender_id();
  return sender_id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Message::set_allocated_sender_id(::std::string* sender_id) {
  if (sender_id != NULL) {
    set_has_sender_id();
  } else {
    clear_has_sender_id();
  }
  sender_id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sender_id);
  // @@protoc_insertion_point(field_set_allocated:MessageProto.Message.sender_id)
}

// repeated .MessageProto.Message.Flags flags = 4;
int Message::flags_size() const {
  return flags_.size();
}
void Message::clear_flags() {
  flags_.Clear();
}
::MessageProto::Message_Flags Message::flags(int index) const {
  // @@protoc_insertion_point(field_get:MessageProto.Message.flags)
  return static_cast< ::MessageProto::Message_Flags >(flags_.Get(index));
}
void Message::set_flags(int index, ::MessageProto::Message_Flags value) {
  assert(::MessageProto::Message_Flags_IsValid(value));
  flags_.Set(index, value);
  // @@protoc_insertion_point(field_set:MessageProto.Message.flags)
}
void Message::add_flags(::MessageProto::Message_Flags value) {
  assert(::MessageProto::Message_Flags_IsValid(value));
  flags_.Add(value);
  // @@protoc_insertion_point(field_add:MessageProto.Message.flags)
}
const ::google::protobuf::RepeatedField<int>&
Message::flags() const {
  // @@protoc_insertion_point(field_list:MessageProto.Message.flags)
  return flags_;
}
::google::protobuf::RepeatedField<int>*
Message::mutable_flags() {
  // @@protoc_insertion_point(field_mutable_list:MessageProto.Message.flags)
  return &flags_;
}

// optional string checksum = 16;
bool Message::has_checksum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void Message::set_has_checksum() {
  _has_bits_[0] |= 0x00000002u;
}
void Message::clear_has_checksum() {
  _has_bits_[0] &= ~0x00000002u;
}
void Message::clear_checksum() {
  checksum_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_checksum();
}
const ::std::string& Message::checksum() const {
  // @@protoc_insertion_point(field_get:MessageProto.Message.checksum)
  return checksum_.GetNoArena();
}
void Message::set_checksum(const ::std::string& value) {
  set_has_checksum();
  checksum_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessageProto.Message.checksum)
}
#if LANG_CXX11
void Message::set_checksum(::std::string&& value) {
  set_has_checksum();
  checksum_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MessageProto.Message.checksum)
}
#endif
void Message::set_checksum(const char* value) {
  set_has_checksum();
  checksum_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessageProto.Message.checksum)
}
void Message::set_checksum(const char* value, size_t size) {
  set_has_checksum();
  checksum_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessageProto.Message.checksum)
}
::std::string* Message::mutable_checksum() {
  set_has_checksum();
  // @@protoc_insertion_point(field_mutable:MessageProto.Message.checksum)
  return checksum_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Message::release_checksum() {
  // @@protoc_insertion_point(field_release:MessageProto.Message.checksum)
  clear_has_checksum();
  return checksum_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Message::set_allocated_checksum(::std::string* checksum) {
  if (checksum != NULL) {
    set_has_checksum();
  } else {
    clear_has_checksum();
  }
  checksum_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), checksum);
  // @@protoc_insertion_point(field_set_allocated:MessageProto.Message.checksum)
}

// optional string payload = 17;
bool Message::has_payload() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void Message::set_has_payload() {
  _has_bits_[0] |= 0x00000004u;
}
void Message::clear_has_payload() {
  _has_bits_[0] &= ~0x00000004u;
}
void Message::clear_payload() {
  payload_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_payload();
}
const ::std::string& Message::payload() const {
  // @@protoc_insertion_point(field_get:MessageProto.Message.payload)
  return payload_.GetNoArena();
}
void Message::set_payload(const ::std::string& value) {
  set_has_payload();
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessageProto.Message.payload)
}
#if LANG_CXX11
void Message::set_payload(::std::string&& value) {
  set_has_payload();
  payload_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MessageProto.Message.payload)
}
#endif
void Message::set_payload(const char* value) {
  set_has_payload();
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessageProto.Message.payload)
}
void Message::set_payload(const char* value, size_t size) {
  set_has_payload();
  payload_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessageProto.Message.payload)
}
::std::string* Message::mutable_payload() {
  set_has_payload();
  // @@protoc_insertion_point(field_mutable:MessageProto.Message.payload)
  return payload_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Message::release_payload() {
  // @@protoc_insertion_point(field_release:MessageProto.Message.payload)
  clear_has_payload();
  return payload_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Message::set_allocated_payload(::std::string* payload) {
  if (payload != NULL) {
    set_has_payload();
  } else {
    clear_has_payload();
  }
  payload_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), payload);
  // @@protoc_insertion_point(field_set_allocated:MessageProto.Message.payload)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace MessageProto

// @@protoc_insertion_point(global_scope)
