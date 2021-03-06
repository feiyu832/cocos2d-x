/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011 Zynga Inc.
 
 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCActionInstant.h"
#include "base_nodes/CCNode.h"
#include "sprite_nodes/CCSprite.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN
//
// InstantAction
//
bool ActionInstant::isDone() const
{
    return true;
}

void ActionInstant::step(float dt) {
    CC_UNUSED_PARAM(dt);
    update(1);
}

void ActionInstant::update(float time) {
    CC_UNUSED_PARAM(time);
    // nothing
}

//
// Show
//

Show* Show::create() 
{
    Show* pRet = new Show();

    if (pRet) {
        pRet->autorelease();
    }

    return pRet;
}

void Show::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setVisible(true);
}

ActionInstant* Show::reverse() const
{
    return Hide::create();
}

Show * Show::clone() const
{
	// no copy constructor
	auto a = new Show();
	a->autorelease();
	return a;
}

//
// Hide
//
Hide * Hide::create() 
{
    Hide *pRet = new Hide();

    if (pRet) {
        pRet->autorelease();
    }

    return pRet;
}

void Hide::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setVisible(false);
}

ActionInstant *Hide::reverse() const
{
    return Show::create();
}

Hide * Hide::clone() const
{
	// no copy constructor
	auto a = new Hide();
	a->autorelease();
	return a;
}

//
// ToggleVisibility
//
ToggleVisibility * ToggleVisibility::create()
{
    ToggleVisibility *pRet = new ToggleVisibility();

    if (pRet)
    {
        pRet->autorelease();
    }

    return pRet;
}

void ToggleVisibility::update(float time) 
{
    CC_UNUSED_PARAM(time);
    _target->setVisible(!_target->isVisible());
}

ToggleVisibility * ToggleVisibility::reverse() const
{
	return ToggleVisibility::create();
}

ToggleVisibility * ToggleVisibility::clone() const
{
	// no copy constructor
	auto a = new ToggleVisibility();
	a->autorelease();
	return a;
}

//
// Remove Self
//
RemoveSelf * RemoveSelf::create(bool isNeedCleanUp /*= true*/) 
{
	RemoveSelf *pRet = new RemoveSelf();

	if (pRet && pRet->init(isNeedCleanUp)) {
		pRet->autorelease();
	}

	return pRet;
}

bool RemoveSelf::init(bool isNeedCleanUp) {
	_isNeedCleanUp = isNeedCleanUp;
	return true;
}

void RemoveSelf::update(float time) {
	CC_UNUSED_PARAM(time);
	_target->removeFromParentAndCleanup(_isNeedCleanUp);
}

RemoveSelf *RemoveSelf::reverse() const
{
	return RemoveSelf::create(_isNeedCleanUp);
}

RemoveSelf * RemoveSelf::clone() const
{
	// no copy constructor
	auto a = new RemoveSelf();
	a->init(_isNeedCleanUp);
	a->autorelease();
	return a;
}

//
// FlipX
//

FlipX *FlipX::create(bool x)
{
    FlipX *pRet = new FlipX();

    if (pRet && pRet->initWithFlipX(x)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool FlipX::initWithFlipX(bool x) {
    _flipX = x;
    return true;
}

void FlipX::update(float time) {
    CC_UNUSED_PARAM(time);
    static_cast<Sprite*>(_target)->setFlipX(_flipX);
}

FlipX* FlipX::reverse() const
{
    return FlipX::create(!_flipX);
}

FlipX * FlipX::clone() const
{
	// no copy constructor
	auto a = new FlipX();
	a->initWithFlipX(_flipX);
	a->autorelease();
	return a;
}
//
// FlipY
//

FlipY * FlipY::create(bool y)
{
    FlipY *pRet = new FlipY();

    if (pRet && pRet->initWithFlipY(y)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool FlipY::initWithFlipY(bool y) {
    _flipY = y;
    return true;
}

void FlipY::update(float time) {
    CC_UNUSED_PARAM(time);
    static_cast<Sprite*>(_target)->setFlipY(_flipY);
}

FlipY* FlipY::reverse() const
{
    return FlipY::create(!_flipY);
}

FlipY * FlipY::clone() const
{
	// no copy constructor
	auto a = new FlipY();
	a->initWithFlipY(_flipY);
	a->autorelease();
	return a;
}

//
// Place
//

Place* Place::create(const Point& pos)
{
    Place *pRet = new Place();

    if (pRet && pRet->initWithPosition(pos)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool Place::initWithPosition(const Point& pos) {
    _position = pos;
    return true;
}

Place * Place::clone() const
{
	// no copy constructor
	auto a = new Place();
	a->initWithPosition(_position);
	a->autorelease();
	return a;
}

Place * Place::reverse() const
{
	// no reverse, just clone
	return this->clone();
}

void Place::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setPosition(_position);
}

//
// CallFunc
//

CallFunc * CallFunc::create(const std::function<void()> &func)
{
    CallFunc *pRet = new CallFunc();

    if (pRet && pRet->initWithFunction(func) ) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CallFunc * CallFunc::create(Object* pSelectorTarget, SEL_CallFunc selector) 
{
    CallFunc *pRet = new CallFunc();

    if (pRet && pRet->initWithTarget(pSelectorTarget)) {
        pRet->_callFunc = selector;
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CallFunc * CallFunc::create(int nHandler)
{
	CallFunc *pRet = new CallFunc();

	if (pRet) {
		pRet->_scriptHandler = nHandler;
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CallFunc::initWithFunction(const std::function<void()> &func)
{
	_function = func;
    return true;
}

bool CallFunc::initWithTarget(Object* pSelectorTarget) {
    if (pSelectorTarget) 
    {
        pSelectorTarget->retain();
    }

    if (_selectorTarget) 
    {
        _selectorTarget->release();
    }

    _selectorTarget = pSelectorTarget;
    return true;
}

CallFunc::~CallFunc(void)
{
    if (_scriptHandler)
    {
        cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_scriptHandler);
    }
    CC_SAFE_RELEASE(_selectorTarget);
}

CallFunc * CallFunc::clone() const
    {
    // no copy constructor
    auto a = new CallFunc();
    if( _selectorTarget) {
        a->initWithTarget(_selectorTarget);
        a->_callFunc = _callFunc;
    }
    else if( _function ){
        a->initWithFunction(_function);
    }
    else if (_scriptHandler > 0 ) {
        a->_scriptHandler = cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine()->reallocateScriptHandler(_scriptHandler);
    }
    

    a->autorelease();
    return a;
}

CallFunc * CallFunc::reverse() const
{
	// no reverse here, just return a clone
	return this->clone();
}

void CallFunc::update(float time) {
    CC_UNUSED_PARAM(time);
    this->execute();
}

void CallFunc::execute() {
    if (_callFunc) {
        (_selectorTarget->*_callFunc)();
    } else if( _function )
		_function();
	if (0 != _scriptHandler) {
        BasicScriptData data((void*)this);
        ScriptEvent event(kCallFuncEvent,(void*)&data);
		ScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
	}
}

//
// CallFuncN
//

CallFuncN * CallFuncN::create(const std::function<void(Node*)> &func)
{
    auto ret = new CallFuncN();

    if (ret && ret->initWithFunction(func) ) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return NULL;
}

// XXX deprecated
CallFuncN * CallFuncN::create(Object* pSelectorTarget, SEL_CallFuncN selector)
{
    CallFuncN *pRet = new CallFuncN();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CallFuncN * CallFuncN::create(int nHandler)
{
	CallFuncN *pRet = new CallFuncN();

	if (pRet) {
		pRet->_scriptHandler = nHandler;
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}


void CallFuncN::execute() {
    if (_callFuncN) {
        (_selectorTarget->*_callFuncN)(_target);
    }
    else if (_functionN) {
        _functionN(_target);
    }
    if (0 != _scriptHandler)
    {
        BasicScriptData data((void*)this,(void*)_target);
        ScriptEvent event(kCallFuncEvent,(void*)&data);
        ScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
    }
}

bool CallFuncN::initWithFunction(const std::function<void (Node *)> &func)
{
    _functionN = func;
    return true;
}

bool CallFuncN::initWithTarget(Object* pSelectorTarget, SEL_CallFuncN selector)
{
    if (CallFunc::initWithTarget(pSelectorTarget)) {
        _callFuncN = selector;
        return true;
    }

    return false;
}

CallFuncN * CallFuncN::clone() const
{
	// no copy constructor
	auto a = new CallFuncN();
	a->initWithTarget(_selectorTarget, _callFuncN);
	a->autorelease();
	return a;
}


NS_CC_END
