/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrImageContext_DEFINED
#define GrImageContext_DEFINED

#include "include/private/GrContext_Base.h"
#include "include/private/GrSingleOwner.h"

class GrImageContextPriv;

// CONTEXT TODO: Remove this once SkImage_Gpu is migrated to holding just a ThreadSafeProxy.
class GrImageContext : public GrContext_Base {
public:
    ~GrImageContext() override;

    // Provides access to functions that aren't part of the public API.
    GrImageContextPriv priv();
    const GrImageContextPriv priv() const;  // NOLINT(readability-const-return-type)

protected:
    friend class GrImageContextPriv; // for hidden functions

    GrImageContext(sk_sp<GrContextThreadSafeProxy>);

    SK_API virtual void abandonContext();
    SK_API virtual bool abandoned();

    /** This is only useful for debug purposes */
    GrSingleOwner* singleOwner() const { return &fSingleOwner; }

    GrImageContext* asImageContext() override { return this; }

private:
    // In debug builds we guard against improper thread handling
    // This guard is passed to the GrDrawingManager and, from there to all the
    // GrSurfaceDrawContexts.  It is also passed to the GrResourceProvider and SkGpuDevice.
    mutable GrSingleOwner            fSingleOwner;

    using INHERITED = GrContext_Base;
};

#endif
