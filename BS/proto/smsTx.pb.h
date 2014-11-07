// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: smsTx.proto

#ifndef PROTOBUF_smsTx_2eproto__INCLUDED
#define PROTOBUF_smsTx_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_smsTx_2eproto();
void protobuf_AssignDesc_smsTx_2eproto();
void protobuf_ShutdownFile_smsTx_2eproto();

class BdfsMsg;
class FsfkMsg;

// ===================================================================

class BdfsMsg : public ::google::protobuf::Message {
 public:
  BdfsMsg();
  virtual ~BdfsMsg();

  BdfsMsg(const BdfsMsg& from);

  inline BdfsMsg& operator=(const BdfsMsg& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BdfsMsg& default_instance();

  void Swap(BdfsMsg* other);

  // implements Message ----------------------------------------------

  BdfsMsg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BdfsMsg& from);
  void MergeFrom(const BdfsMsg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 nSerialId = 1;
  inline bool has_nserialid() const;
  inline void clear_nserialid();
  static const int kNSerialIdFieldNumber = 1;
  inline ::google::protobuf::uint32 nserialid() const;
  inline void set_nserialid(::google::protobuf::uint32 value);

  // required uint32 nSourceAddress = 2;
  inline bool has_nsourceaddress() const;
  inline void clear_nsourceaddress();
  static const int kNSourceAddressFieldNumber = 2;
  inline ::google::protobuf::uint32 nsourceaddress() const;
  inline void set_nsourceaddress(::google::protobuf::uint32 value);

  // required uint32 nDestAddress = 3;
  inline bool has_ndestaddress() const;
  inline void clear_ndestaddress();
  static const int kNDestAddressFieldNumber = 3;
  inline ::google::protobuf::uint32 ndestaddress() const;
  inline void set_ndestaddress(::google::protobuf::uint32 value);

  // required uint32 nMsgType = 4;
  inline bool has_nmsgtype() const;
  inline void clear_nmsgtype();
  static const int kNMsgTypeFieldNumber = 4;
  inline ::google::protobuf::uint32 nmsgtype() const;
  inline void set_nmsgtype(::google::protobuf::uint32 value);

  // required uint32 nInfoLen = 5;
  inline bool has_ninfolen() const;
  inline void clear_ninfolen();
  static const int kNInfoLenFieldNumber = 5;
  inline ::google::protobuf::uint32 ninfolen() const;
  inline void set_ninfolen(::google::protobuf::uint32 value);

  // required string sInfoBuff = 6;
  inline bool has_sinfobuff() const;
  inline void clear_sinfobuff();
  static const int kSInfoBuffFieldNumber = 6;
  inline const ::std::string& sinfobuff() const;
  inline void set_sinfobuff(const ::std::string& value);
  inline void set_sinfobuff(const char* value);
  inline void set_sinfobuff(const char* value, size_t size);
  inline ::std::string* mutable_sinfobuff();
  inline ::std::string* release_sinfobuff();
  inline void set_allocated_sinfobuff(::std::string* sinfobuff);

  // @@protoc_insertion_point(class_scope:BdfsMsg)
 private:
  inline void set_has_nserialid();
  inline void clear_has_nserialid();
  inline void set_has_nsourceaddress();
  inline void clear_has_nsourceaddress();
  inline void set_has_ndestaddress();
  inline void clear_has_ndestaddress();
  inline void set_has_nmsgtype();
  inline void clear_has_nmsgtype();
  inline void set_has_ninfolen();
  inline void clear_has_ninfolen();
  inline void set_has_sinfobuff();
  inline void clear_has_sinfobuff();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 nserialid_;
  ::google::protobuf::uint32 nsourceaddress_;
  ::google::protobuf::uint32 ndestaddress_;
  ::google::protobuf::uint32 nmsgtype_;
  ::std::string* sinfobuff_;
  ::google::protobuf::uint32 ninfolen_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_smsTx_2eproto();
  friend void protobuf_AssignDesc_smsTx_2eproto();
  friend void protobuf_ShutdownFile_smsTx_2eproto();

  void InitAsDefaultInstance();
  static BdfsMsg* default_instance_;
};
// -------------------------------------------------------------------

class FsfkMsg : public ::google::protobuf::Message {
 public:
  FsfkMsg();
  virtual ~FsfkMsg();

  FsfkMsg(const FsfkMsg& from);

  inline FsfkMsg& operator=(const FsfkMsg& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FsfkMsg& default_instance();

  void Swap(FsfkMsg* other);

  // implements Message ----------------------------------------------

  FsfkMsg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FsfkMsg& from);
  void MergeFrom(const FsfkMsg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 nSerialId = 1;
  inline bool has_nserialid() const;
  inline void clear_nserialid();
  static const int kNSerialIdFieldNumber = 1;
  inline ::google::protobuf::uint32 nserialid() const;
  inline void set_nserialid(::google::protobuf::uint32 value);

  // required uint32 nRes = 2;
  inline bool has_nres() const;
  inline void clear_nres();
  static const int kNResFieldNumber = 2;
  inline ::google::protobuf::uint32 nres() const;
  inline void set_nres(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:FsfkMsg)
 private:
  inline void set_has_nserialid();
  inline void clear_has_nserialid();
  inline void set_has_nres();
  inline void clear_has_nres();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 nserialid_;
  ::google::protobuf::uint32 nres_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_smsTx_2eproto();
  friend void protobuf_AssignDesc_smsTx_2eproto();
  friend void protobuf_ShutdownFile_smsTx_2eproto();

  void InitAsDefaultInstance();
  static FsfkMsg* default_instance_;
};
// ===================================================================


// ===================================================================

// BdfsMsg

// required uint32 nSerialId = 1;
inline bool BdfsMsg::has_nserialid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BdfsMsg::set_has_nserialid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BdfsMsg::clear_has_nserialid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BdfsMsg::clear_nserialid() {
  nserialid_ = 0u;
  clear_has_nserialid();
}
inline ::google::protobuf::uint32 BdfsMsg::nserialid() const {
  return nserialid_;
}
inline void BdfsMsg::set_nserialid(::google::protobuf::uint32 value) {
  set_has_nserialid();
  nserialid_ = value;
}

// required uint32 nSourceAddress = 2;
inline bool BdfsMsg::has_nsourceaddress() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BdfsMsg::set_has_nsourceaddress() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BdfsMsg::clear_has_nsourceaddress() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BdfsMsg::clear_nsourceaddress() {
  nsourceaddress_ = 0u;
  clear_has_nsourceaddress();
}
inline ::google::protobuf::uint32 BdfsMsg::nsourceaddress() const {
  return nsourceaddress_;
}
inline void BdfsMsg::set_nsourceaddress(::google::protobuf::uint32 value) {
  set_has_nsourceaddress();
  nsourceaddress_ = value;
}

// required uint32 nDestAddress = 3;
inline bool BdfsMsg::has_ndestaddress() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BdfsMsg::set_has_ndestaddress() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BdfsMsg::clear_has_ndestaddress() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BdfsMsg::clear_ndestaddress() {
  ndestaddress_ = 0u;
  clear_has_ndestaddress();
}
inline ::google::protobuf::uint32 BdfsMsg::ndestaddress() const {
  return ndestaddress_;
}
inline void BdfsMsg::set_ndestaddress(::google::protobuf::uint32 value) {
  set_has_ndestaddress();
  ndestaddress_ = value;
}

// required uint32 nMsgType = 4;
inline bool BdfsMsg::has_nmsgtype() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BdfsMsg::set_has_nmsgtype() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BdfsMsg::clear_has_nmsgtype() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BdfsMsg::clear_nmsgtype() {
  nmsgtype_ = 0u;
  clear_has_nmsgtype();
}
inline ::google::protobuf::uint32 BdfsMsg::nmsgtype() const {
  return nmsgtype_;
}
inline void BdfsMsg::set_nmsgtype(::google::protobuf::uint32 value) {
  set_has_nmsgtype();
  nmsgtype_ = value;
}

// required uint32 nInfoLen = 5;
inline bool BdfsMsg::has_ninfolen() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BdfsMsg::set_has_ninfolen() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BdfsMsg::clear_has_ninfolen() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BdfsMsg::clear_ninfolen() {
  ninfolen_ = 0u;
  clear_has_ninfolen();
}
inline ::google::protobuf::uint32 BdfsMsg::ninfolen() const {
  return ninfolen_;
}
inline void BdfsMsg::set_ninfolen(::google::protobuf::uint32 value) {
  set_has_ninfolen();
  ninfolen_ = value;
}

// required string sInfoBuff = 6;
inline bool BdfsMsg::has_sinfobuff() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void BdfsMsg::set_has_sinfobuff() {
  _has_bits_[0] |= 0x00000020u;
}
inline void BdfsMsg::clear_has_sinfobuff() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void BdfsMsg::clear_sinfobuff() {
  if (sinfobuff_ != &::google::protobuf::internal::kEmptyString) {
    sinfobuff_->clear();
  }
  clear_has_sinfobuff();
}
inline const ::std::string& BdfsMsg::sinfobuff() const {
  return *sinfobuff_;
}
inline void BdfsMsg::set_sinfobuff(const ::std::string& value) {
  set_has_sinfobuff();
  if (sinfobuff_ == &::google::protobuf::internal::kEmptyString) {
    sinfobuff_ = new ::std::string;
  }
  sinfobuff_->assign(value);
}
inline void BdfsMsg::set_sinfobuff(const char* value) {
  set_has_sinfobuff();
  if (sinfobuff_ == &::google::protobuf::internal::kEmptyString) {
    sinfobuff_ = new ::std::string;
  }
  sinfobuff_->assign(value);
}
inline void BdfsMsg::set_sinfobuff(const char* value, size_t size) {
  set_has_sinfobuff();
  if (sinfobuff_ == &::google::protobuf::internal::kEmptyString) {
    sinfobuff_ = new ::std::string;
  }
  sinfobuff_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BdfsMsg::mutable_sinfobuff() {
  set_has_sinfobuff();
  if (sinfobuff_ == &::google::protobuf::internal::kEmptyString) {
    sinfobuff_ = new ::std::string;
  }
  return sinfobuff_;
}
inline ::std::string* BdfsMsg::release_sinfobuff() {
  clear_has_sinfobuff();
  if (sinfobuff_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = sinfobuff_;
    sinfobuff_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BdfsMsg::set_allocated_sinfobuff(::std::string* sinfobuff) {
  if (sinfobuff_ != &::google::protobuf::internal::kEmptyString) {
    delete sinfobuff_;
  }
  if (sinfobuff) {
    set_has_sinfobuff();
    sinfobuff_ = sinfobuff;
  } else {
    clear_has_sinfobuff();
    sinfobuff_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// FsfkMsg

// required uint32 nSerialId = 1;
inline bool FsfkMsg::has_nserialid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FsfkMsg::set_has_nserialid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FsfkMsg::clear_has_nserialid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FsfkMsg::clear_nserialid() {
  nserialid_ = 0u;
  clear_has_nserialid();
}
inline ::google::protobuf::uint32 FsfkMsg::nserialid() const {
  return nserialid_;
}
inline void FsfkMsg::set_nserialid(::google::protobuf::uint32 value) {
  set_has_nserialid();
  nserialid_ = value;
}

// required uint32 nRes = 2;
inline bool FsfkMsg::has_nres() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FsfkMsg::set_has_nres() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FsfkMsg::clear_has_nres() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FsfkMsg::clear_nres() {
  nres_ = 0u;
  clear_has_nres();
}
inline ::google::protobuf::uint32 FsfkMsg::nres() const {
  return nres_;
}
inline void FsfkMsg::set_nres(::google::protobuf::uint32 value) {
  set_has_nres();
  nres_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_smsTx_2eproto__INCLUDED
