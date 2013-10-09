/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Meecast for Tizen2
 *
 * Copyright (C) 2013 Vlad Vasilyeu
 *     for the code
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU  General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 * You should have received a copy of the GNU  General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
*/
/*******************************************************************************/
#include <FApp.h>
#include "meecastAppereanceForm.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;

static const int LIST_HEIGHT = 112;
static const int BUTTON_HEIGHT = 74;
static const RequestId SEND_RELOAD_CONFIG = 200;

meecastAppereanceForm::meecastAppereanceForm(void)
                            : __pList(null)
{
}

meecastAppereanceForm::~meecastAppereanceForm(void)
{
}

bool
meecastAppereanceForm::Initialize(void)
{
    Construct(L"APPEARANCE_FORM");
    return true;
}

result
meecastAppereanceForm::OnInitializing(void)
{
    result r = E_SUCCESS;

    SetFormBackEventListener(this);
	CreateGroupedListView();

    Header* pHeader = GetHeader();
    pHeader->SetTitleText(_("Appereance"));

	// Create Custom Element
//	__pCustomGroupedListElement = new (std::nothrow) CustomGroupedListElement();
/*
	__pItemContext = new (std::nothrow) ListContextItem();
	__pItemContext->Construct();
	__pItemContext->AddElement(1, L"Button 1");
	__pItemContext->AddElement(2, L"Button 2");
*/
    __pList->SetItemChecked(1,1, true);
    __pList->RequestRedraw();

    return r;
}


void
meecastAppereanceForm::CreateGroupedListView(void)
{
	__pList = static_cast <GroupedListView*> (GetControl("IDC_GROUPEDLISTVIEW"));
	__pList->SetItemProvider(*this);
	__pList->AddGroupedListViewItemEventListener(*this);
	AddControl(*__pList);
}

result
meecastAppereanceForm::OnTerminating(void)
{
    result r = E_SUCCESS;
	// Deallocate bitmaps
    // TODO:
    // Add your termination code here
    return r;
}

void
meecastAppereanceForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
    SceneManager* pSceneManager = SceneManager::GetInstance();
    AppAssert(pSceneManager);

    AppLog("Check Action");
    switch(actionId)
    {
    default:
        break;
    }
}

void
meecastAppereanceForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->GoBackward(BackwardSceneTransition(SCENE_TRANSITION_ANIMATION_TYPE_RIGHT));

}

void
meecastAppereanceForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
                                          const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
    // TODO:
    // Add your scene activate code here
    AppLog("OnSceneActivatedN Settings");
}

void
meecastAppereanceForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
                                           const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
    // TODO:
    // Add your scene deactivate code here
    AppLog("OnSceneDeactivated");
}


ListItemBase*
meecastAppereanceForm::CreateItem(int groupIndex, int itemIndex, int itemWidth)
{

    ConfigTizen *config;
    config = ConfigTizen::Instance( std::string("config.xml"),
                                       Core::AbstractConfig::prefix+
                                       Core::AbstractConfig::schemaPath+
                                       "config.xsd");
 
//	ListAnnexStyle style =  LIST_ANNEX_STYLE_RADIO;
//	CustomItem* pItem = new (std::nothrow) CustomItem();
//	pItem->Construct(Tizen::Graphics::Dimension(GetClientAreaBounds().width, 90),style);

     CustomItem* pItem = new (std::nothrow) CustomItem();
    TryReturn(pItem != null, null, "Out of memory");

    pItem->Construct(Tizen::Graphics::Dimension(itemWidth, LIST_HEIGHT), LIST_ANNEX_STYLE_ONOFF_SLIDING);
    String* pStr;

   switch (groupIndex){
        case 0:
            switch (itemIndex % 8){
            case 0:
                pStr = new String (_("Widget in LockScreen"));
                pItem->AddElement(Tizen::Graphics::Rectangle(16, 32, 700, 50), 0, *pStr, 36,
                                  Tizen::Graphics::Color(Tizen::Graphics::Color::GetColor(COLOR_ID_GREY)),
                                  Tizen::Graphics::Color(Tizen::Graphics::Color::GetColor(COLOR_ID_GREY)),
                                  Tizen::Graphics::Color(Tizen::Graphics::Color::GetColor(COLOR_ID_GREY)), true);
//                if (_config->Gps())
 //                   __pListView->SetItemChecked(index, true);
  //              else
 //                   __pListView->SetItemChecked(index, false);
                break;


            default:
                break;
            }
            break;
         case 1: 
            switch (itemIndex % 8){
            case 0:
                pStr = new String (_("Widget in LockScreen"));
                pItem->AddElement(Tizen::Graphics::Rectangle(16, 32, 700, 50), 0, *pStr, 36,
                                  Tizen::Graphics::Color(Color::GetColor(COLOR_ID_GREY)),
                                  Tizen::Graphics::Color(Color::GetColor(COLOR_ID_GREY)),
                                  Tizen::Graphics::Color(Color::GetColor(COLOR_ID_GREY)), true);
//                if (_config->Gps())
//                    __pListView->SetItemChecked(index, true);
  //              else
 //                   __pListView->SetItemChecked(index, false);
                break;


            default:
                break;
            }
            break;

    }
	return pItem;
}

int
meecastAppereanceForm::GetGroupCount(void)
{
	return 2;
}

int
meecastAppereanceForm::GetItemCount(int groupIndex)
{
	int itemCount = 0;
	switch(groupIndex)
	{
	case 0:
		itemCount = 1;
		break;
	case 1:
		itemCount = 2;
		break;

	default:
		break;
	}
	return itemCount;
}


bool
meecastAppereanceForm::DeleteItem(int groupIndex, int itemIndex, Controls::ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

bool
meecastAppereanceForm::DeleteGroupItem(int groupIndex, Controls::GroupItem* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

GroupItem*
meecastAppereanceForm::CreateGroupItem(int groupIndex, int itemWidth)
{
	GroupItem* pItem = new (std::nothrow) GroupItem();

	pItem->Construct(Tizen::Graphics::Dimension(GetClientAreaBounds().width, 80));
	String text(L"");
	switch (groupIndex)
	{
        case 0:
            text = _("Settings for Lockscreen widget");
            break;
        case 1:
            text = _("Widget");
            break;
	}
	pItem->SetElement(text, null);
	return pItem;
}


void
meecastAppereanceForm::OnGroupedListViewItemStateChanged(GroupedListView& listView, int groupIndex, int itemIndex, int elementId, ListItemStatus state)
{
    ConfigTizen *config;
    config = ConfigTizen::Instance( std::string("config.xml"),
                                       Core::AbstractConfig::prefix+
                                       Core::AbstractConfig::schemaPath+
                                       "config.xsd");
    if (state == LIST_ITEM_STATUS_CHECKED){
        switch (groupIndex){
            case 0:
                switch (itemIndex % 8){
                case 0:
                    AppLog("Selected2");
                    config->UpdatePeriod(INT_MAX);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                    __pList->SetItemChecked(groupIndex, itemIndex + 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 4, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 5, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 6, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 7, false);
                    break;
                case 1:
                    AppLog("Selected3");
                    config->UpdatePeriod(15*60);
                    __pList->SetItemChecked(groupIndex, itemIndex - 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                    __pList->SetItemChecked(groupIndex, itemIndex + 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 4, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 5, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 6, false);
                   break;
                case 2:
                    config->UpdatePeriod(30*60);
                    __pList->SetItemChecked(groupIndex, itemIndex - 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                    __pList->SetItemChecked(groupIndex, itemIndex + 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 4, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 5, false);
                   break;
                 case 3:
                    config->UpdatePeriod(1*3600);
                    __pList->SetItemChecked(groupIndex, itemIndex - 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                    __pList->SetItemChecked(groupIndex, itemIndex + 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 4, false);
                   break;
                 case 4:
                    config->UpdatePeriod(2*3600);
                    __pList->SetItemChecked(groupIndex, itemIndex - 4, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                    __pList->SetItemChecked(groupIndex, itemIndex + 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 3, false);
                   break;
                 case 5:
                    config->UpdatePeriod(4*3600);
                    __pList->SetItemChecked(groupIndex, itemIndex - 5, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 4, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                    __pList->SetItemChecked(groupIndex, itemIndex + 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex + 2, false);
                   break;
                 case 6:
                    config->UpdatePeriod(12*3600);
                    __pList->SetItemChecked(groupIndex, itemIndex - 6, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 5, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 4, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                    __pList->SetItemChecked(groupIndex, itemIndex + 1, false);
                   break;
                 case 7:
                    config->UpdatePeriod(24*3600);
                    __pList->SetItemChecked(groupIndex, itemIndex - 7, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 6, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 5, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 4, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 3, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 2, false);
                    __pList->SetItemChecked(groupIndex, itemIndex - 1, false);
                    __pList->SetItemChecked(groupIndex, itemIndex, true);
                   break;

                default:
                    break;
                }
                break;
       }
    } 
    config->saveConfig();
    __pList->UpdateList();
    App* pApp = App::GetInstance();
    pApp->SendUserEvent(SEND_RELOAD_CONFIG, null);

}


