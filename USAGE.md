# User Manual

## Table of Contents
* [Table of Contents](#table-of-contents)
* [1 Introduction](#1-introduction)
* [2 Menus](#2-menus)
    * [2.1 Warps](#21-warps)
    * [2.2 Cheats](#22-cheats)
    * [2.3 Inventory](#23-inventory)
        * [2.3.1 Items](#231-items)
        * [2.3.2 Masks](#232-masks)
        * [2.3.3 Quest Status](#233-shield)
        * [2.3.4 Amounts](#234-sword)
        * [2.3.5 Remains](#235-remains)
        * [2.3.6 Ocarina Songs](#236-ocarina-songs)
    * [2.4 Equips](#24-equips)
    * [2.5 Watches](#25-watches)
    
    * [2.6 Equips](#26-equips)
    
    * [2.8 Debug](#28-debug)
        * [2.8.1 Actors](#281-actors)
* [3 Commands](#3-commands)
* [4 Save](#4-save)
    * [4.1 Memfiles](#41-memfiles)

## 1 Introduction
The main interface for the practice menu, is used by bringing up the menu which by default is done by pressing the `L + R + Select` Buttons.  

The menu is navigated with the dpad buttons, and items are activated with the `A` button. 

The patch also implements the following features beyond the menu:
* Actor watches

If/when rebinding the activate menu command, you find yourself in a state where the menu cannot be activated, pressing L+R+X+B+Dpad Left will reset ALL settings to their default values, or if you saved your profile will revert to those.  

## 2 Menus
### 2.1 Warps
The warps menu contains a listing of all the entrances in the game categorized into 13 categories.  These categories are based on the dungeons, bosses, clock town, houses, shops, other miscellaneous scenes, as well as overworlds including the moon.  Under each category is a listing of scenes, if a scene has multiple entrances selecting that scene will enter a menu with all available entrances. Selecting an entrance will immediately warp you to that entrance.  If a scene only has one entrance, selecting that scene will warp you to that single entrance.

There is also a way to manually enter the entrance index, if you know where to go.

### 2.2 Cheats
The chaet menu lets you modify data that pertains to the current save file.

**Refill Health** sets your current health to whatever your max hearts are.

**Refill Magic** sets your current magic to whatever your max magic meter is.

**Refill Rupees** sets your current rupee count to 999.

**Change Day** will allow you to change which day you are on

**Change Time of Day** will allow you to change what the current time of day is.  

Hours are typically incremented by 0xAAA, but this is not exact in all cases.

**Change Flow of Time** allows you to change how quickly the 3 day timer is moving.

**ISG** Toggles the sword_active bit which allows for infinite ISG.

**Edit Link's Info** There are a few options within Link's Player Data that is easy to swap.
- You can adjust the total health of link within here. If you multiply by 16, it gives you a full heart. 
- Magic upgrade can be adjusted to 0 or 1 to give you upgraded magic or stock magic.
- Razord Sword Hits Remaining adjusts the amount of razor sword hits that you have before it breaks.
- Modify ruppee count adjusts the current amount of rupees you have.

### 2.3 Inventory
This is the main inventory editor in kz which has the following submenus:
#### 2.3.1 Items
This is a listing of the items that are available on the **Select Item** Subscreen in the pause menu.  Selecting any of the items will make that item available in your inventory. If you dupe over any items, they will be unselected from this menu.  
Selecting a bottle will also open up a submenu that will allow you to choose an item to place in the bottle. 

#### 2.3.2 Masks
This is a listing of all the masks that are available on the **Masks** Subscreen.  Selecting any of the masks will make them available in your inventory. If you dupe over any items, they will be unselected from this menu.

#### 2.3.3 Shield
This listing will allow you to select which shield you wish to use.

#### 2.3.4 Sword
This listing will allow you to select which sword you wish to use. Currently there is an issue with the Razor Sword as it does not have a hit counter assigned to it.

#### 2.3.5 Remains
This submenu allows you to select which remains you have obtained.

#### 2.3.6 Ocarina Songs
Enable and disables which songs you have obtained.

### 2.4 Equips
The equips tab lets you adjust what is on your face buttons and what can be used. These values show as integers, but are actually hex values. The item list can be found [here](https://github.com/PhlexPlexico/mm3d-practice-tools/blob/eaa119fe17afbb3a1780a31c331d183ca8627cc6/source/game/items.h#L9). As an example, take the bottle which is item ID `0x12`. Converted to an integer it would be `18` in the menu.

***Warning:*** While you may be able to equip any of these items to you buttons, using them may cause the game to crash. 

### 2.5 Watches
The watches menu contains a list of dots as you load it (if no watches are saved). Once clicking A on one, you can give it a name, a type(signed/unsigned/hex/float 8/16/32 bit), and whether or not to draw it on the screen. Once you know the address you're looking for, you can scroll over the `Addr:` and use A to select the portion of the address to edit. Once complete, and selected to draw, you will find it on the bottom screen. If it's invalid, it will produce `Invalid Address`.


### 2.8 Debug
The debug menu allows you to see and modify at a lower level to what is happening within the game.  There is currently one menu for Actors.

#### 2.8.1 Actors
The actor menu will show you a list of all currently loaded actors in the game. These can be filtered by using L+R to find various types of actors. These contain the following:
- All
- Switch
- BG (Background)
- Player (You!)
- Explosives
- NPC
- Enemy
- Prop
- Item Actions
- Misc
- Boss
- Door
- Chest


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
* reset inputs - Reset inputs to a default state, either by your profile if it exists, or the above defaults. `L+R+X+B+LEFT`

## 4 Save
The saving menu currently has the functionality to store your button combinations for commands to the SD card (known as your "profile"). This way, it becomes a portable JSON file that you can share with your friends, or move to another system if yours breaks.  
Included with this is the saving of watches as well. Instead of having to re-write the address on game load every time, you can save the watches to a file and have them load on game load.  
Within both of these menus, you can also press Y to delete the file from your SD card, in case you wish to start over.

### 4.1 Memfiles
Memfiles are a sort of psuedo-savestate. They are much simpler than true save states, but still allow for powerful practice.  
A memfile saves the entirety of the save context, as well as a few of Link's modifiers such as his location on the map, and his velocity.
When a memfile is loaded from the menu, it will reload the area and place Link where he was when the save was initiated.