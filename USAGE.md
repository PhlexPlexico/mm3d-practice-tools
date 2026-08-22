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
        * [2.3.3 Shield](#233-shield)
        * [2.3.4 Sword](#234-sword)
        * [2.3.5 Remains](#235-remains)
        * [2.3.6 Ocarina Songs](#236-ocarina-songs)
    * [2.4 Gear](#24-gear)
    * [2.5 Equips](#25-equips)
    * [2.6 Watches](#26-watches)
    * [2.7 Debug](#27-debug)
        * [2.7.1 Week Event Flags](#271-week-event-flags)
        * [2.7.2 Actors](#272-actors)
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

**Infinite Items** opens a list of the consumables - deku sticks, deku nuts, bombs, arrows, bombchus, magic beans and powder kegs. Anything switched on here is kept topped up every frame rather than filled once, so you can practice something that burns through ammo without stopping to refill.

**Change Day** will allow you to change which day you are on

**Change Time of Day** will allow you to change what the current time of day is.  

Hours are typically incremented by 0xAAA, but this is not exact in all cases.

**Change Flow of Time** allows you to change how quickly the 3 day timer is moving.

**ISG** Toggles the sword_active bit which allows for infinite ISG.

Editing link's own values used to live here as **Edit Link's Info**. It is its own menu now - see [2.4 Gear](#24-gear).

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

### 2.4 Gear
The gear menu edits the values that show on the gear screen in game. This was the **Edit Link's Info** submenu under cheats, moved out and filled in, since none of it is really a cheat.

**Total Health** adjusts link's maximum health. If you multiply by 16, it gives you a full heart.

**Magic** sets how much magic link has, from 0 to 3. 0 takes it away entirely, and while it is 0 nothing that needs magic will work, including the lens of truth. 1 is the standard meter and 2 is the upgraded one. 3 gives you Chateau Romani, which keeps the meter full and lets you spend magic for free.

**Razor Sword Hits Remaining** adjusts the amount of razor sword hits that you have before it breaks.

**Rupee Count** adjusts the current amount of rupees you have.

**Bomb Bag** and **Quiver** pick which upgrade you have, or none at all.

**Bomber's Notebook** gives you the notebook or takes it away.

**Trade Item 1**, **Trade Item 2**, **Room Key** and **Special Delivery to Mama** hold the trade quest items. The game keeps one slot per chain and swaps whatever is in it rather than stacking them up, so picking a new item replaces the one that was there. Moon's tear and all four title deeds share the first slot, kafei's letter and the pendant of memories share the second, and the room key and the special delivery have one each.

### 2.5 Equips
The equips tab lets you adjust what is on your face buttons and what can be used. These values show as integers, but are actually hex values. The item list can be found [here](https://github.com/PhlexPlexico/mm3d-practice-tools/blob/eaa119fe17afbb3a1780a31c331d183ca8627cc6/source/game/items.h#L9). As an example, take the bottle which is item ID `0x12`. Converted to an integer it would be `18` in the menu.

***Warning:*** While you may be able to equip any of these items to you buttons, using them may cause the game to crash. 

### 2.6 Watches
The watches menu contains a list of dots as you load it (if no watches are saved). Once clicking A on one, you can give it a name, a type(signed/unsigned/hex/float 8/16/32 bit), and whether or not to draw it on the screen. Once you know the address you're looking for, you can scroll over the `Addr:` and use A to select the portion of the address to edit. Once complete, and selected to draw, you will find it on the bottom screen. If it's invalid, it will produce `Invalid Address`.

Once you have selected the `Addr:` line with A, there are two ways to change it. The dpad nudges the highlighted byte, which is handy for walking to an address near the one you already have. For anything else, press X to bring up a keypad and type the address out.

The keypad starts with whatever the address already is, so correcting a digit or two does not mean typing all eight again. Move around it with the dpad or circle pad and press A to pick a key. `Del` removes the last digit, `Clr` empties the whole thing, and `OK` accepts what you have typed. B backs out and leaves the address as it was. If you type fewer than eight digits the rest are treated as leading zeroes, so `7751D8` and `007751D8` are the same address.


### 2.7 Debug
The debug menu allows you to see and modify at a lower level to what is happening within the game.  There are menus for week event flags and for actors.

#### 2.7.1 Week Event Flags
The game keeps 140 single byte registers of event state - who you have spoken to, what you have handed over, which cutscenes have played. This menu lists all of them with their current value spelled out in bits, so a register with anything set in it stands out without opening it.

Pressing A on one opens its eight flags as a list you can toggle. Where the flag has a known name it is shown, and where it does not you get the bit number instead. Left and right page through the list.

***Warning:*** These are the same flags the game uses to decide what has happened in your cycle. Turning one on out of order can leave a quest in a state the game never expects to see.

#### 2.7.2 Actors
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
* store position - stores the current coords of link into the selected slot `L+R+LEFT`
* restore position - moves link back to the location in the selected slot `L+R+RIGHT`
* previous position - selects the previous position slot `L+R+DOWN+LEFT`
* next position - selects the next position slot `L+R+DOWN+RIGHT`
* pause - pauses the game on the current frame `L+R+UP`
* advance - advances a single frame `UP`
* toggle watches - displays active watches on the bottom screen.
* reset inputs - Reset inputs to a default state, either by your profile if it exists, or the above defaults. `L+R+X+B+LEFT`

There are eight position slots rather than one, so you can keep a few setups on the go at once and compare them. Store and restore always work on whichever slot is selected, and the previous/next commands move between them without opening the menu.

Whenever you store, restore, or change slot, the slot number appears at the top of the upper screen for a couple of seconds, in the same spot `PAUSED` uses. Trying to restore a slot you have not stored anything into yet will say so rather than dropping link somewhere unexpected.

The slots are written to the SD card as soon as you store one, and read back when the game loads, so they survive turning the console off.

## 4 Save
The saving menu currently has the functionality to store your button combinations for commands to the SD card (known as your "profile"). This way, it becomes a portable file that you can share with your friends, or move to another system if yours breaks.  
Included with this is the saving of watches as well. Instead of having to re-write the address on game load every time, you can save the watches to a file and have them load on game load.  
Your stored positions are saved here too, though you do not need to come here for them - they are written out the moment you store one. The entry is for saving on demand, or for clearing them out.  
Within each of these menus, you can also press Y to delete the file from your SD card, in case you wish to start over.

### 4.1 Memfiles
Memfiles are a sort of psuedo-savestate. They are much simpler than true save states, but still allow for powerful practice.  
A memfile saves the entirety of the save context, as well as a few of Link's modifiers such as his location on the map, and his velocity.
When a memfile is loaded from the menu, it will reload the area and place Link where he was when the save was initiated.