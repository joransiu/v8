// Copyright 2011 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_STORE_BUFFER_H_
#define V8_STORE_BUFFER_H_

#include "src/allocation.h"
#include "src/base/logging.h"
#include "src/base/platform/platform.h"
#include "src/globals.h"
#include "src/heap/slot-set.h"

namespace v8 {
namespace internal {

// Intermediate buffer that accumulates old-to-new stores from the generated
// code. On buffer overflow the slots are moved to the remembered set.
class StoreBuffer {
 public:
  explicit StoreBuffer(Heap* heap);
  static void StoreBufferOverflow(Isolate* isolate);
  void SetUp();
  void TearDown();

  static const int kStoreBufferOverflowBit = 1 << (14 + kPointerSizeLog2);
  static const int kStoreBufferSize = kStoreBufferOverflowBit;
  static const int kStoreBufferLength = kStoreBufferSize / sizeof(Address);

  void MoveEntriesToRememberedSet();

 private:
  Heap* heap_;

  // The start and the limit of the buffer that contains store slots
  // added from the generated code.
  Address* start_;
  Address* limit_;

  base::VirtualMemory* virtual_memory_;
};

}  // namespace internal
}  // namespace v8

#endif  // V8_STORE_BUFFER_H_
