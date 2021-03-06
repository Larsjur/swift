#include "isPrespecialized.h"
#include <swift/Runtime/Metadata.h>

using namespace swift;

namespace llvm {
  int DisableABIBreakingChecks;
  int EnableABIBreakingChecks;
}

bool isCanonicalStaticallySpecializedGenericMetadata(Metadata *self) {
  if (auto *metadata = dyn_cast<StructMetadata>(self)) {
    return metadata->isCanonicalStaticallySpecializedGenericMetadata();
  }
  if (auto *metadata = dyn_cast<EnumMetadata>(self))
    return metadata->isCanonicalStaticallySpecializedGenericMetadata();
  if (auto *metadata = dyn_cast<ClassMetadata>(self))
    return metadata->isCanonicalStaticallySpecializedGenericMetadata();

  return false;
}

int isCanonicalStaticallySpecializedGenericMetadata(void *ptr) {
  auto metadata = static_cast<Metadata *>(ptr);
  auto isCanonical =
      isCanonicalStaticallySpecializedGenericMetadata(metadata);
  return isCanonical;
}

void allocateDirtyAndFreeChunk(void) {
  uintptr_t ChunkSize = 16 * 1024;

  char *allocation = new char[ChunkSize];

  memset(allocation, 255, ChunkSize);

  delete[] allocation;
}
