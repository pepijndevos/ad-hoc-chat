// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Message.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace MessageProto {

namespace {

const ::google::protobuf::Descriptor* Message_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Message_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Message_Flags_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_Message_2eproto() {
  protobuf_AddDesc_Message_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Message.proto");
  GOOGLE_CHECK(file != NULL);
  Message_descriptor_ = file->message_type(0);
  static const int Message_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, seq_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, msg_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, sender_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, flags_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, checksum_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, payload_),
  };
  Message_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Message_descriptor_,
      Message::default_instance_,
      Message_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Message, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Message));
  Message_Flags_descriptor_ = Message_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Message_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Message_descriptor_, &Message::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Message_2eproto() {
  delete Message::default_instance_;
  delete Message_reflection_;
}

void protobuf_AddDesc_Message_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rMessage.proto\022\014MessageProto\"\305\001\n\007Messag"
    "e\022\013\n\003seq\030\001 \001(\005\022\016\n\006msg_id\030\002 \001(\005\022\021\n\tsender"
    "_id\030\003 \001(\t\022*\n\005flags\030\004 \003(\0162\033.MessageProto."
    "Message.Flags\022\020\n\010checksum\030\020 \001(\t\022\017\n\007paylo"
    "ad\030\021 \001(\t\";\n\005Flags\022\r\n\tCONNECTED\020\000\022\n\n\006LEAD"
    "ER\020\001\022\010\n\004VOTE\020\002\022\r\n\tCANDIDATE\020\003", 229);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Message.proto", &protobuf_RegisterTypes);
  Message::default_instance_ = new Message();
  Message::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Message_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Message_2eproto {
  StaticDescriptorInitializer_Message_2eproto() {
    protobuf_AddDesc_Message_2eproto();
  }
} static_descriptor_initializer_Message_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* Message_Flags_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Message_Flags_descriptor_;
}
bool Message_Flags_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Message_Flags Message::CONNECTED;
const Message_Flags Message::LEADER;
const Message_Flags Message::VOTE;
const Message_Flags Message::CANDIDATE;
const Message_Flags Message::Flags_MIN;
const Message_Flags Message::Flags_MAX;
const int Message::Flags_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Message::kSeqFieldNumber;
const int Message::kMsgIdFieldNumber;
const int Message::kSenderIdFieldNumber;
const int Message::kFlagsFieldNumber;
const int Message::kChecksumFieldNumber;
const int Message::kPayloadFieldNumber;
#endif  // !_MSC_VER

Message::Message()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MessageProto.Message)
}

void Message::InitAsDefaultInstance() {
}

Message::Message(const Message& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MessageProto.Message)
}

void Message::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  seq_ = 0;
  msg_id_ = 0;
  sender_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  checksum_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  payload_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Message::~Message() {
  // @@protoc_insertion_point(destructor:MessageProto.Message)
  SharedDtor();
}

void Message::SharedDtor() {
  if (sender_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete sender_id_;
  }
  if (checksum_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete checksum_;
  }
  if (payload_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete payload_;
  }
  if (this != default_instance_) {
  }
}

void Message::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Message::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Message_descriptor_;
}

const Message& Message::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Message_2eproto();
  return *default_instance_;
}

Message* Message::default_instance_ = NULL;

Message* Message::New() const {
  return new Message;
}

void Message::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Message*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 55) {
    ZR_(seq_, msg_id_);
    if (has_sender_id()) {
      if (sender_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        sender_id_->clear();
      }
    }
    if (has_checksum()) {
      if (checksum_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        checksum_->clear();
      }
    }
    if (has_payload()) {
      if (payload_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        payload_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  flags_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Message::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MessageProto.Message)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(16383);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 seq = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &seq_)));
          set_has_seq();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_msg_id;
        break;
      }

      // optional int32 msg_id = 2;
      case 2: {
        if (tag == 16) {
         parse_msg_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &msg_id_)));
          set_has_msg_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_sender_id;
        break;
      }

      // optional string sender_id = 3;
      case 3: {
        if (tag == 26) {
         parse_sender_id:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sender_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->sender_id().data(), this->sender_id().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "sender_id");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_flags;
        break;
      }

      // repeated .MessageProto.Message.Flags flags = 4;
      case 4: {
        if (tag == 32) {
         parse_flags:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::MessageProto::Message_Flags_IsValid(value)) {
            add_flags(static_cast< ::MessageProto::Message_Flags >(value));
          } else {
            mutable_unknown_fields()->AddVarint(4, value);
          }
        } else if (tag == 34) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedEnumNoInline(
                 input,
                 &::MessageProto::Message_Flags_IsValid,
                 this->mutable_flags())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_flags;
        if (input->ExpectTag(130)) goto parse_checksum;
        break;
      }

      // optional string checksum = 16;
      case 16: {
        if (tag == 130) {
         parse_checksum:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_checksum()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->checksum().data(), this->checksum().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "checksum");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(138)) goto parse_payload;
        break;
      }

      // optional string payload = 17;
      case 17: {
        if (tag == 138) {
         parse_payload:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_payload()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->payload().data(), this->payload().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "payload");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
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
      "sender_id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->sender_id(), output);
  }

  // repeated .MessageProto.Message.Flags flags = 4;
  for (int i = 0; i < this->flags_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->flags(i), output);
  }

  // optional string checksum = 16;
  if (has_checksum()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->checksum().data(), this->checksum().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "checksum");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      16, this->checksum(), output);
  }

  // optional string payload = 17;
  if (has_payload()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "payload");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      17, this->payload(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MessageProto.Message)
}

::google::protobuf::uint8* Message::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
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
      "sender_id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->sender_id(), target);
  }

  // repeated .MessageProto.Message.Flags flags = 4;
  for (int i = 0; i < this->flags_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      4, this->flags(i), target);
  }

  // optional string checksum = 16;
  if (has_checksum()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->checksum().data(), this->checksum().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "checksum");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        16, this->checksum(), target);
  }

  // optional string payload = 17;
  if (has_payload()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->payload().data(), this->payload().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "payload");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        17, this->payload(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MessageProto.Message)
  return target;
}

int Message::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
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

  }
  // repeated .MessageProto.Message.Flags flags = 4;
  {
    int data_size = 0;
    for (int i = 0; i < this->flags_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
        this->flags(i));
    }
    total_size += 1 * this->flags_size() + data_size;
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Message::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Message* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Message*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Message::MergeFrom(const Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  flags_.MergeFrom(from.flags_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_seq()) {
      set_seq(from.seq());
    }
    if (from.has_msg_id()) {
      set_msg_id(from.msg_id());
    }
    if (from.has_sender_id()) {
      set_sender_id(from.sender_id());
    }
    if (from.has_checksum()) {
      set_checksum(from.checksum());
    }
    if (from.has_payload()) {
      set_payload(from.payload());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Message::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Message::CopyFrom(const Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Message::IsInitialized() const {

  return true;
}

void Message::Swap(Message* other) {
  if (other != this) {
    std::swap(seq_, other->seq_);
    std::swap(msg_id_, other->msg_id_);
    std::swap(sender_id_, other->sender_id_);
    flags_.Swap(&other->flags_);
    std::swap(checksum_, other->checksum_);
    std::swap(payload_, other->payload_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Message::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Message_descriptor_;
  metadata.reflection = Message_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace MessageProto

// @@protoc_insertion_point(global_scope)
