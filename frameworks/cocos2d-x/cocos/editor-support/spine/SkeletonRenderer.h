/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SKELETONRENDERER_H_
#define SPINE_SKELETONRENDERER_H_

#include <spine/spine.h>
#include "cocos2d.h"

namespace spine {

class AttachmentVertices;

/* Draws a skeleton. */
class SkeletonRenderer: public cocos2d::Node, public cocos2d::BlendProtocol {
public:
	CREATE_FUNC(SkeletonRenderer);
	static SkeletonRenderer* createWithSkeleton(spSkeleton* skeleton, bool ownsSkeleton = false, bool ownsSkeletonData = false);
	static SkeletonRenderer* createWithData (spSkeletonData* skeletonData, bool ownsSkeletonData = false);
	static SkeletonRenderer* createWithFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	static SkeletonRenderer* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);

	virtual void update (float deltaTime) override;
	virtual void draw (cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
	virtual void drawDebug (cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags);
	virtual cocos2d::Rect getBoundingBox () const override;
	virtual void onEnter () override;
	virtual void onExit () override;

	spSkeleton* getSkeleton();

	void setTimeScale(float scale);
	float getTimeScale() const;

	/*  */
	void setDebugSlotsEnabled(bool enabled);
	bool getDebugSlotsEnabled() const;

	void setDebugBonesEnabled(bool enabled);
	bool getDebugBonesEnabled() const;
	
	void setDebugMeshesEnabled(bool enabled);
	bool getDebugMeshesEnabled() const;

	void setDebugPointEnabled(bool enabled);
	bool getDebugPointEnabled() const;

	void setDebugBoundingBoxEnabled(bool enabled);
	bool getDebugBoundingBoxEnabled() const;

	void setDebugPathEnabled(bool enabled);
	bool getDebugPathEnabled() const;

	// --- Convenience methods for common Skeleton_* functions.
	void updateWorldTransform ();

	void setToSetupPose ();
	void setBonesToSetupPose ();
	void setSlotsToSetupPose ();

	/* Returns 0 if the bone was not found. */
	spBone* findBone (const std::string& boneName) const;
	/* Returns 0 if the slot was not found. */
	spSlot* findSlot (const std::string& slotName) const;
	
	/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
	 * attached if the corresponding attachment from the old skin was attached. Returns false if the skin was not found.
	 * @param skin May be empty string ("") for no skin.*/
	bool setSkin (const std::string& skinName);
	/** @param skin May be 0 for no skin.*/
	bool setSkin (const char* skinName);
	
	/* Returns 0 if the slot or attachment was not found. */
	spAttachment* getAttachment (const std::string& slotName, const std::string& attachmentName) const;
	/* Returns false if the slot or attachment was not found.
	 * @param attachmentName May be empty string ("") for no attachment. */
	bool setAttachment (const std::string& slotName, const std::string& attachmentName);
	/* @param attachmentName May be 0 for no attachment. */
	bool setAttachment (const std::string& slotName, const char* attachmentName);
	
	/* Enables/disables two color tinting for this instance. May break batching */
	void setTwoColorTint(bool enabled);
	/* Whether two color tinting is enabled */
	bool isTwoColorTint();
	
	/* Sets the vertex effect to be used, set to 0 to disable vertex effects */
	void setVertexEffect(spVertexEffect* effect);
	
	/* Sets the range of slots that should be rendered. Use -1, -1 to clear the range */
	void setSlotsRange(int startSlotIndex, int endSlotIndex);

    void setFlippedX(int flippedX);
    void setFlippedY(int flippedY);

    // --- BlendProtocol
	virtual void setBlendFunc (const cocos2d::BlendFunc& blendFunc)override;
	virtual const cocos2d::BlendFunc& getBlendFunc () const override;
	virtual void setOpacityModifyRGB (bool value) override;
	virtual bool isOpacityModifyRGB () const override;
	
	// Frees global memory used for temporay vertex transformations.
	static void destroyScratchBuffers();

CC_CONSTRUCTOR_ACCESS:
	SkeletonRenderer ();
	SkeletonRenderer(spSkeleton* skeleton, bool ownsSkeleton = false, bool ownsSkeletonData = false);
	SkeletonRenderer (spSkeletonData* skeletonData, bool ownsSkeletonData = false);
	SkeletonRenderer (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	SkeletonRenderer (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);

	virtual ~SkeletonRenderer ();

	void initWithSkeleton(spSkeleton* skeleton, bool ownsSkeleton = false, bool ownsSkeletonData = false);
	void initWithData (spSkeletonData* skeletonData, bool ownsSkeletonData = false);
	void initWithJsonFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	void initWithJsonFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
	void initWithBinaryFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	void initWithBinaryFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);

	virtual void initialize ();
	
protected:
	void setSkeletonData (spSkeletonData* skeletonData, bool ownsSkeletonData);
	virtual AttachmentVertices* getAttachmentVertices (spRegionAttachment* attachment) const;
	virtual AttachmentVertices* getAttachmentVertices (spMeshAttachment* attachment) const;
	void setupGLProgramState(bool twoColorTintEnabled);

	bool _ownsSkeletonData;
	bool _ownsSkeleton;
	spAtlas* _atlas;
	spAttachmentLoader* _attachmentLoader;
	cocos2d::CustomCommand _debugCommand;
	cocos2d::BlendFunc _blendFunc;
	bool _premultipliedAlpha;
	spSkeleton* _skeleton;
	float _timeScale;
	bool _debugSlots;
	bool _debugBones;
	bool _debugMeshes;
	bool _debugPoint;
	bool _debugBoundingBox;
	bool _debugPath;
	spSkeletonClipping* _clipper;
	spVertexEffect* _effect;
	
	int _startSlotIndex;
	int _endSlotIndex;
};

}

#endif /* SPINE_SKELETONRENDERER_H_ */