#include "CCDirector.hpp"
#include "CCTransitionPlayLayer.hpp"

void HookedCCDirector::onModify(auto& self) {
    (void)self.setHookPriorityPost("cocos2d::CCDirector::replaceScene", geode::Priority::Last);
}

bool HookedCCDirector::replaceScene(cocos2d::CCScene* scene) {
    if (!scene) return CCDirector::replaceScene(scene);

    auto transition = geode::cast::typeinfo_cast<cocos2d::CCTransitionFade*>(scene);
    if (!transition || !transition->m_pInScene || !transition->m_pOutScene) {
        return CCDirector::replaceScene(scene);
    }

    // Only replace fades that are actually entering gameplay. This keeps the
    // hook out of unrelated fades from GD or other mods.
    auto playLayer = transition->m_pInScene->getChildByType<PlayLayer>(0);
    if (!playLayer) {
        return CCDirector::replaceScene(scene);
    }

    static void* vtable = []() -> void* {
        CCTransitionPlayLayer temp;
        // dtor releases both of these
        temp.m_pInScene = cocos2d::CCScene::create();
        temp.m_pOutScene = cocos2d::CCScene::create();
        return *(void**)&temp;
    }();

    *(void**)scene = vtable;
    return CCDirector::replaceScene(scene);
}
