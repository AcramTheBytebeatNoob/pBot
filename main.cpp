#include <Geode/Geode.hpp>

using namespace geode::prelude;

class pBotMenu : public FLAlertLayer {
protected:
    CCScale9Sprite* m_pbotBg;
    CCMenu* m_mainBotTab;
    CCMenu* m_downloaderTab;
    CCMenu* m_changelogTab;
    CCLabelBMFont* m_statusLabel;

public:
    static pBotMenu* create() {
        auto ret = new pBotMenu();
        if (ret && ret->init(390.0f, 250.0f, "GJ_square02.png", "pBot Studio")) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init(float width, float height, const char* bg_image, const char* title) {
        if (!FLAlertLayer::init(width, height, bg_image, title)) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        // --- BLUE-BOX DESIGN ---
        if (m_mainLayer->getChildrenCount() > 0) {
            m_pbotBg = static_cast<CCScale9Sprite*>(m_mainLayer->getChildren()->objectAtIndex(0));
            if (m_pbotBg) {
                m_pbotBg->setColor({ 10, 35, 70 }); 
                m_pbotBg->setOpacity(230);
            }
        }

        auto staticMenu = CCMenu::create();
        staticMenu->setPosition({0, 0});
        this->addChild(staticMenu);

        auto titleLabel = CCLabelBMFont::create("pBot Engine v2.0", "goldFont.fnt");
        titleLabel->setScale(0.75f);
        titleLabel->setPosition({ winSize.width / 2, winSize.height / 2 + (height / 2) - 18 });
        staticMenu->addChild(titleLabel);

        auto closeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
            this, menu_selector(pBotMenu::onClose)
        );
        closeBtn->setPosition({ winSize.width / 2 + (width / 2) - 15, winSize.height / 2 + (height / 2) - 15 });
        staticMenu->addChild(closeBtn);

        // Dein epischer Kommentar als permanentes Status-Label
        m_statusLabel = CCLabelBMFont::create("THIS WILL BE MORE POWERFUL THAN XDBOT AND ZBOT EVER.", "chatFont.fnt");
        m_statusLabel->setScale(0.42f);
        m_statusLabel->setColor({ 0, 255, 255 }); 
        m_statusLabel->setPosition({ winSize.width / 2, winSize.height / 2 - (height / 2) + 14 });
        this->addChild(m_statusLabel);

        // ==========================================
        // TAB 1: MAIN BOT PANEL
        // ==========================================
        m_mainBotTab = CCMenu::create();
        m_mainBotTab->setPosition({0, 0});
        this->addChild(m_mainBotTab);

        float coreY = winSize.height / 2 + 10;
        createCheckboxRow(m_mainBotTab, "Record Macro", { winSize.width / 2 - 120, coreY }, menu_selector(pBotMenu::onRecordToggle));
        createCheckboxRow(m_mainBotTab, "Play Replay", { winSize.width / 2 + 10, coreY }, menu_selector(pBotMenu::onPlayToggle));

        createActionButton(m_mainBotTab, "Save", { winSize.width / 2 - 60, coreY - 45 }, menu_selector(pBotMenu::onSaveClick), "GJ_longBtn01_001.png"); 
        createActionButton(m_mainBotTab, "Load", { winSize.width / 2 + 60, coreY - 45 }, menu_selector(pBotMenu::onLoadClick), "GJ_longBtn02_001.png"); 

        // ==========================================
        // TAB 2: MACRO LISTE
        // ==========================================
        m_downloaderTab = CCMenu::create();
        m_downloaderTab->setPosition({0, 0});
        m_downloaderTab->setVisible(false);
        this->addChild(m_downloaderTab);

        auto macroCard = CCScale9Sprite::createWithSpriteFrameName("GJ_square05.png");
        macroCard->setContentSize({ 280, 55 });
        macroCard->setPosition({ winSize.width / 2, winSize.height / 2 + 15 });
        macroCard->setColor({ 15, 25, 45 });
        m_downloaderTab->addChild(macroCard);

        auto macroTitle = CCLabelBMFont::create("Tax Evasion (Unnerved) - 100% FPS Fix", "bigFont.fnt");
        macroTitle->setScale(0.35f);
        macroTitle->setPosition({ 10, 42 });
        macroTitle->setAnchorPoint({ 0, 0.5 });
        macroCard->addChild(macroTitle);

        auto commentText = CCLabelBMFont::create("Comment: 'Bro this bypasses the physics steps perfectly!' - AlexGD", "chatFont.fnt");
        commentText->setScale(0.45f);
        commentText->setColor({ 180, 180, 180 });
        commentText->setPosition({ 10, 20 });
        commentText->setAnchorPoint({ 0, 0.5 });
        macroCard->addChild(commentText);

        auto dlSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"); 
        dlSprite->setScale(0.4f);
        auto dlBtn = CCMenuItemSpriteExtra::create(dlSprite, this, menu_selector(pBotMenu::onPlayMacro));
        dlBtn->setPosition({ winSize.width / 2 + 115, winSize.height / 2 + 15 });
        m_downloaderTab->addChild(dlBtn);

        // ==========================================
        // TAB 3: INTEGRATED CHANGELOG
        // ==========================================
        m_changelogTab = CCMenu::create();
        m_changelogTab->setPosition({0, 0});
        m_changelogTab->setVisible(false);
        this->addChild(m_changelogTab);

        auto changelogText = CCLabelBMFont::create(
            "pBot v2.0 Changelog:\n"
            "- Added integrated offline macro catalog\n"
            "- Added developer comment rendering system\n"
            "- Frame-perfect local ticks natively supported\n"
            "- XDBOT and ZBOT logic successfully surpassed.", 
            "chatFont.fnt"
        );
        changelogText->setScale(0.55f);
        changelogText->setPosition({ winSize.width / 2, winSize.height / 2 + 15 });
        changelogText->setAlignment(kCCTextAlignmentLeft);
        m_changelogTab->addChild(changelogText);

        // --- SIDE & CORNER BUTTONS ---
        auto folderSprite = CCSprite::createWithSpriteFrameName("GJ_folderBtn_001.png");
        auto folderBtn = CCMenuItemSpriteExtra::create(folderSprite, this, menu_selector(pBotMenu::onFolderClick));
        folderBtn->setPosition({ winSize.width / 2 - (width / 2) + 25, winSize.height / 2 - (height / 2) + 38 });
        staticMenu->addChild(folderBtn);

        auto settingsSprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        settingsSprite->setScale(0.75f);
        auto settingsBtn = CCMenuItemSpriteExtra::create(settingsSprite, this, menu_selector(pBotMenu::onSettingsClick));
        settingsBtn->setPosition({ winSize.width / 2 + (width / 2) - 25, winSize.height / 2 - (height / 2) + 38 });
        staticMenu->addChild(settingsBtn);

        float tabX = winSize.width / 2 - (width / 2) - 20;
        createTabButton(staticMenu, "Bot", { tabX, winSize.height / 2 + 40 }, menu_selector(pBotMenu::switchTabBot));
        createTabButton(staticMenu, "List", { tabX, winSize.height / 2 }, menu_selector(pBotMenu::switchTabCloud));
        createTabButton(staticMenu, "Logs", { tabX, winSize.height / 2 - 40 }, menu_selector(pBotMenu::switchTabLogs));

        return true;
    }

    void switchTabBot(CCObject*) {
        m_mainBotTab->setVisible(true); m_downloaderTab->setVisible(false); m_changelogTab->setVisible(false);
    }
    void switchTabCloud(CCObject*) {
        m_mainBotTab->setVisible(false); m_downloaderTab->setVisible(true); m_changelogTab->setVisible(false);
    }
    void switchTabLogs(CCObject*) {
        m_mainBotTab->setVisible(false); m_downloaderTab->setVisible(false); m_changelogTab->setVisible(true);
    }

    void onPlayMacro(CCObject*) { log::info("Playing Macro from list..."); }
    void onSettingsClick(CCObject*) { log::info("Opening Settings..."); }
    void onFolderClick(CCObject*) { log::info("Opening Folder..."); }
    void onRecordToggle(CCObject*) { log::info("Record Toggled"); }
    void onPlayToggle(CCObject*) { log::info("Play Toggled"); }
    void onSaveClick(CCObject*) { log::info("Macro Saved!"); }
    void onLoadClick(CCObject*) { log::info("Macro Loaded!"); }
    void onClose(CCObject*) { this->keyBackClicked(); }

private:
    void createCheckboxRow(CCMenu* menu, const char* text, CCPoint position, SEL_MenuHandler callback) {
        auto checkbox = CCMenuItemToggler::create(
            CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
            CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"), this, callback
        );
        checkbox->setPosition(position);
        menu->addChild(checkbox);

        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        label->setScale(0.35f);
        label->setAnchorPoint({0.0f, 0.5f});
        label->setPosition({ position.x + 16, position.y });
        menu->getParent()->addChild(label); 
    }

    void createActionButton(CCMenu* menu, const char* text, CCPoint position, SEL_MenuHandler callback, const char* texture) {
        auto btnSprite = CCScale9Sprite::createWithSpriteFrameName(texture);
        btnSprite->setContentSize({ 90, 24 });
        auto btnText = CCLabelBMFont::create(text, "bigFont.fnt");
        btnText->setScale(0.35f);
        btnText->setPosition({ btnSprite->getContentSize().width / 2, btnSprite->getContentSize().height / 2 });
        btnSprite->addChild(btnText);

        auto btn = CCMenuItemSpriteExtra::create(btnSprite, this, callback);
        btn->setPosition(position);
        menu->addChild(btn);
    }

    void createTabButton(CCMenu* menu, const char* text, CCPoint position, SEL_MenuHandler callback) {
        auto spr = CCScale9Sprite::createWithSpriteFrameName("GJ_longBtn06_001.png"); 
        spr->setContentSize({ 45, 20 });
        auto label = CCLabelBMFont::create(text, "bigFont.fnt");
        label->setScale(0.25f);
        label->setPosition({ spr->getContentSize().width / 2, spr->getContentSize().height / 2 });
        spr->addChild(label);

        auto btn = CCMenuItemSpriteExtra::create(spr, this, callback);
        btn->setPosition(position);
        menu->addChild(btn);
    }
};
