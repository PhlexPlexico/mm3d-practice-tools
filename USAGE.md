# User Manual

## 0 Table of Contents
* [0 Table of Contents](#0-table-of-contents)
* [1 Introduction](#1-introduction)
* [2 Menus](#2-menus)
    * [2.1 Warps](#21-warps)
    * [2.2 Cheats](#22-cheats)
    * [2.3 Scene](#23-scene)
    * [2.4 Watches](#24-watches)
    * [2.5 Inventory](#25-inventory)
        * [2.5.1 Items](#251-items)
        * [2.5.2 Masks](#252-masks)
        * [2.5.3 Quest Status](#253-shield)
        * [2.5.4 Amounts](#254-sword)
        * [2.5.5 Remains](#255-remains)
        * [2.5.6 Ocarina Songs](#256-ocarina-songs)
        * [2.5.7 Ocarina Songs](#257-amounts)
    * [2.6 Equips](#26-equips)
    * [2.7 Cheats](#27-cheats)
    * [2.8 Debug](#28-debug)
        * [2.8.3 Actors](#283-actors)
* [3 Commands](#3-commands)

## 1 Introduction
The main interface for the practice menu, is used by bringing up the menu which by default is done by pressing the `L + R + Select` Buttons.  

The menu is navigated with the dpad buttons, and items are activated with the `A` button. 

The patch also implements the following features beyond the menu:
* Actor watches

If/when rebinding the activate menu command, you find yourself in a state where the menu cannot be activated, entering the konami code (up up down down left right left right B A) will reset ALL settings to their default values.  

## 2 Menus
### 2.1 Warps
The warps menu contains a listing of all the entrances in the game categorized into 7 categories.  These categories are based on the central clock town area, the 4 cardinal directions of normal gameplay, overworld, and other miscellaneous scenes.  Under each category is a listing of scenes, if a scene has multiple entrances selecting that scene will enter a menu with all available entrances. Selecting an entrance will immediately warp you to that entrance.  If a scene only has one entrance, selecting that scene will warp you to that single entrance.

***Warning:*** Warping while not in a normal playing state of the game (spinning n64 logo, file select screen) will cause *undefined beahvior*

### 2.4 Watches
TODO: Explanation


### 2.5 Inventory
This is the main inventory editor in kz which has the following submenus:
#### 2.5.1 Items
This is a listing of the items that are available on the **Select Item** Subscreen in the pause menu.  Selecting any of the items will make that item available in your inventory. 


#### 2.5.2 Masks
This is a listing of all the masks that are available on the **Masks** Subscreen.  Selecting any of the masks will make them available in your inventory

#### 2.5.3 Shield
This listing will allow you to select which shield you wish to use.

#### 2.5.4 Sword
This listing will allow you to select which sword you wish to use.

#### 2.5.5 Remains
This submenu allows you to select which remains you have obtained.

#### 2.5.6 Ocarina Songs
Enable and disables which songs you have obtained.

#### 2.5.7 Amounts
The **amounts** menu allows you to change the ammo amounts for items in your inventory as well as the current amount of magic and health that you have.  

### 2.6 Equips
The equips menu allows you to change your currently equiped sword and shield as well as which items are equipped on the B Button, and X/Y/I/II.  Changing which sword is equipped will also change the sword/shield you have in the **Gear** Subscreen.  

Selecting the B Button equip, or one of the three C Button equips will bring up a hex value. Please refer to an item table to see what values you can give yourself.

***Warning:*** While you may be able to equip any of these items to you buttons, using them may cause the game to crash. 

### 2.7 Cheats
The chaet menu lets you modify data that pertains to the current save file.

**Refill Health** sets your current health to whatever your max hearts are.

**Refill Magic** sets your current magic to whatever your max magic meter is.

**Refill Rupees** sets your current rupee count to 999.

**Change Day** will allow you to change which day you are on

**Change Time of Day** will allow you to change what the current time of day is.  

Hours are typically incremented by 0xAAA, but this is not exact in all cases.

**Change Flow of Time** allows you to change how quickly the 3 day timer is moving.

**ISG** Toggles the sword_active bit which allows for ISG.

**Edit Link's Info** There are a few 

### 2.8 Debug
The debug menu allows you to see and modify at a lower level to what is happening within the game.  There are 4 different menus.

#### 2.8.1 Actors
TODO Explanation


## 3 Commands
The practice patch implements the following commands 
* toggle menu - opens or closes the main menu `L+R+SEL`
* levitate - classic "L to levitate" causes links to rise when held `X+A`
* fall - allows link to immediately reach ground `L+R+DOWN+Y`
* run fast - allows link to run at a really fast speed `X+Y`
* go back to file select - allows you to load a different save `Y+A`
* reload scene - reloads the current scene at the last entrance `L+R+DOWN+A`
* void out - activates a void out `L+R+DOWN+B`
* store position - stores the current coords of link `L+R+LEFT`
* restore position - moves link back to the current location `L+R+RIGHT`
* pause - pauses the game on the current frame `L+R+UP`
* advance - advances a single frame `UP`
* toggle watches - displays active watches on the bottom screen.
