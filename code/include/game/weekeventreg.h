/**
 * @file weekeventreg.h
 * @author phlexplexico (https://github.com/phlexplexico/)
 * @brief
 * @date 2025-11-12
 *
 */
#pragma once

namespace game {
  union WeekEventReg00 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_00_01;
    BitField<1, 1, u8> WEEKEVENTREG_ENTERED_TERMINA_FIELD;
    BitField<2, 1, u8> WEEKEVENTREG_ENTERED_IKANA_GRAVEYARD;
    BitField<3, 1, u8> WEEKEVENTREG_ENTERED_ROMANI_RANCH;
    BitField<4, 2, u8> WEEKEVENTREG_ENTERED_GORMAN_TRACK;
    BitField<5, 1, u8> WEEKEVENTREG_ENTERED_MOUNTAIN_VILLAGE_WINTER;
    BitField<6, 1, u8> WEEKEVENTREG_ENTERED_GORON_SHRINE;
    BitField<7, 1, u8> WEEKEVENTREG_ENTERED_SNOWHEAD;
  };

  union WeekEventReg01 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_ENTERED_WOODFALL_TEMPLE;
    BitField<1, 1, u8> WEEKEVENTREG_ENTERED_SNOWHEAD_TEMPLE;
    BitField<2, 1, u8> WEEKEVENTREG_ENTERED_GREAT_BAY_TEMPLE;
    BitField<3, 1, u8> WEEKEVENTREG_ENTERED_STONE_TOWER_TEMPLE;
    BitField<4, 1, u8> WEEKEVENTREG_COMPLETED_WOODFALL_TEMPLE;
    BitField<5, 1, u8> WEEKEVENTREG_COMPLETED_SNOWHEAD_TEMPLE;
    BitField<6, 1, u8> WEEKEVENTREG_COMPLETED_GREAT_BAY_TEMPLE;
    BitField<7, 1, u8> WEEKEVENTREG_COMPLETED_STONE_TOWER_TEMPLE;
  };

  // Attached to the scene but unused. Entrance cutscene is instead triggered by `ACTOR_OBJ_DEMO`
  union WeekEventReg02 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_ENTERED_IKANA_CASTLE;
    BitField<1, 1, u8> WEEKEVENTREG_ENTERED_STONE_TOWER;
    BitField<2, 1, u8> WEEKEVENTREG_ENTERED_STONE_TOWER_INVERTED;
    BitField<3, 1, u8> WEEKEVENTREG_ENTERED_EAST_CLOCK_TOWN;
    BitField<4, 1, u8> WEEKEVENTREG_ENTERED_WEST_CLOCK_TOWN;
    BitField<5, 1, u8> WEEKEVENTREG_ENTERED_NORTH_CLOCK_TOWN;
    BitField<6, 1, u8> WEEKEVENTREG_ENTERED_WOODFALL_TEMPLE;
    BitField<7, 1, u8> WEEKEVENTREG_ENTERED_SNOWHEAD_TEMPLE;
  };

  // Attached to the scene but unused. Entrance cutscene is instead triggered by `ACTOR_OBJ_DEMO`
  union WeekEventReg03 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_ENTERED_PIRATES_FORTRESS_EXTERIOR;
    BitField<1, 1, u8> WEEKEVENTREG_ENTERED_STONE_TOWER_TEMPLE;
    BitField<2, 1, u8> WEEKEVENTREG_ENTERED_STONE_TOWER_TEMPLE_INVERTED;
    // Unused as no cutscene is attached to this script
    BitField<3, 1, u8> WEEKEVENTREG_ENTERED_THE_MOON;
    BitField<4, 1, u8> WEEKEVENTREG_ENTERED_MOON_DEKU_TRIAL;
    BitField<5, 1, u8> WEEKEVENTREG_ENTERED_MOON_GORON_TRIAL;
    BitField<6, 1, u8> WEEKEVENTREG_ENTERED_MOON_ZORA_TRIAL;
    BitField<7, 1, u8> WEEKEVENTREG_03_80;
  };

  union WeekEventReg04 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_04_01;
    BitField<1, 1, u8> WEEKEVENTREG_04_02;
    BitField<2, 1, u8> WEEKEVENTREG_04_04;
    BitField<3, 1, u8> WEEKEVENTREG_04_08;
    BitField<4, 1, u8> WEEKEVENTREG_04_10;
    BitField<5, 1, u8> WEEKEVENTREG_04_20;
    BitField<6, 1, u8> WEEKEVENTREG_04_40;
    BitField<7, 1, u8> WEEKEVENTREG_04_80;
  };

  union WeekEventReg05 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_05_01;
    BitField<1, 1, u8> WEEKEVENTREG_05_02;
    BitField<2, 1, u8> WEEKEVENTREG_05_04;
    BitField<3, 1, u8> WEEKEVENTREG_05_08;
    BitField<4, 1, u8> WEEKEVENTREG_05_10;
    BitField<5, 1, u8> WEEKEVENTREG_05_20;
    BitField<6, 1, u8> WEEKEVENTREG_05_40;
    BitField<7, 1, u8> WEEKEVENTREG_05_80;
  };

  union WeekEventReg06 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_06_01;
    BitField<1, 1, u8> WEEKEVENTREG_06_02;
    BitField<2, 1, u8> WEEKEVENTREG_06_04;
    BitField<3, 1, u8> WEEKEVENTREG_06_08;
    BitField<4, 1, u8> WEEKEVENTREG_06_10;
    BitField<5, 1, u8> WEEKEVENTREG_06_20;
    BitField<6, 1, u8> WEEKEVENTREG_06_40;
    BitField<7, 1, u8> WEEKEVENTREG_06_80;
  };

  union WeekEventReg07 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_07_01;
    BitField<1, 1, u8> WEEKEVENTREG_07_02;
    BitField<2, 1, u8> WEEKEVENTREG_07_04;
    BitField<3, 1, u8> WEEKEVENTREG_07_08;
    BitField<4, 1, u8> WEEKEVENTREG_07_10;
    BitField<5, 1, u8> WEEKEVENTREG_07_20;
    BitField<6, 1, u8> WEEKEVENTREG_07_40;
    BitField<7, 1, u8> WEEKEVENTREG_ENTERED_WOODFALL_TEMPLE_PRISON;
  };

  union WeekEventReg08 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_08_01;
    BitField<1, 1, u8> WEEKEVENTREG_08_02;
    BitField<2, 1, u8> WEEKEVENTREG_08_04;
    BitField<3, 1, u8> WEEKEVENTREG_08_08;
    BitField<4, 1, u8> WEEKEVENTREG_08_10;
    BitField<5, 1, u8> WEEKEVENTREG_RECEIVED_DOGGY_RACETRACK_HEART_PIECE;
    // This is set under three circumstances:
    // 1. The player watches the cutscene of the Clock Tower opening.
    // 2. The player sees the Clock Tower opening outside of a cutscene. After the first cycle, this
    //    can be seen in Termina Field or in North, East, or West Clock Town.
    // 3. The player enters Termina Field or North, South, East, or West Clock Town any time after
    //    midnight on the Final Day.
    // Thus, it is possible for the player to be in the final six hours and still have this unset; all
    // the player needs to do is avoid certain areas.
    BitField<6, 1, u8> WEEKEVENTREG_CLOCK_TOWER_OPENED;
    BitField<7, 1, u8> WEEKEVENTREG_08_80;
  };

  union WeekEventReg09 {
    u8 raw;
    // This 5 flags are managed in a special way by EnElfgrp
    BitField<0, 1, u8> WEEKEVENTREG_09_01;
    BitField<1, 1, u8> WEEKEVENTREG_09_02;
    BitField<2, 1, u8> WEEKEVENTREG_09_04;
    BitField<3, 1, u8> WEEKEVENTREG_09_08;
    BitField<4, 1, u8> WEEKEVENTREG_09_10;

    BitField<5, 1, u8> WEEKEVENTREG_09_20;
    BitField<6, 1, u8> WEEKEVENTREG_09_40;
    BitField<7, 1, u8> WEEKEVENTREG_09_80;
  };

  union WeekEventReg10 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_TALKED_TINGLE;
    BitField<1, 1, u8> WEEKEVENTREG_10_02;
    BitField<2, 1, u8> WEEKEVENTREG_10_04;
    BitField<3, 1, u8> WEEKEVENTREG_RECEIVED_BANK_WALLET_UPGRADE;
    BitField<4, 1, u8> WEEKEVENTREG_10_10;
    BitField<5, 1, u8> WEEKEVENTREG_10_20;
    BitField<6, 1, u8> WEEKEVENTREG_10_40;
    BitField<7, 1, u8> WEEKEVENTREG_10_80;
  };

  union WeekEventReg11 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_11_01;
    BitField<1, 1, u8> WEEKEVENTREG_11_02;
    BitField<2, 1, u8> WEEKEVENTREG_11_04;
    BitField<3, 1, u8> WEEKEVENTREG_11_08;
    BitField<4, 1, u8> WEEKEVENTREG_11_10;
    BitField<5, 1, u8> WEEKEVENTREG_11_20;
    BitField<6, 1, u8> WEEKEVENTREG_11_40;
    BitField<7, 1, u8> WEEKEVENTREG_11_80;  // XXX: Possible collected fairy from clocktown.
  };

  union WeekEventReg12 {
    u8 raw;

    // woodfall temple wood flower opened
    BitField<0, 1, u8> WEEKEVENTREG_12_01;

    BitField<1, 1, u8> WEEKEVENTREG_12_02;
    BitField<2, 1, u8> WEEKEVENTREG_12_04;
    BitField<3, 1, u8> WEEKEVENTREG_SAVED_KOUME;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_KOTAKE_BOTTLE;
    BitField<5, 1, u8> WEEKEVENTREG_12_20;  // CT Guard Allows you through without talking.
    BitField<6, 1, u8> WEEKEVENTREG_12_40;
    BitField<7, 1, u8> WEEKEVENTREG_12_80;
  };

  union WeekEventReg13 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_13_01;
    BitField<1, 1, u8> WEEKEVENTREG_13_02;
    BitField<2, 1, u8> WEEKEVENTREG_13_04;
    BitField<3, 1, u8> WEEKEVENTREG_13_08;
    BitField<4, 1, u8> WEEKEVENTREG_13_10;

    // This flag marks that the player has finished the Oceanside Spider House and has exited.
    // Used to identify if EnSth should be moved deeper into the house.
    // This does NOT flag:
    //   A) that the player has completed the house (Inventory_GetSkullTokenCount(play->sceneId))
    //   B) that the player has collected a reward (WEEKEVENTREG_OCEANSIDE_SPIDER_HOUSE_COLLECTED_REWARD)
    //   C) that the player has collected the wallet (WEEKEVENTREG_RECEIVED_OCEANSIDE_WALLET_UPGRADE)
    BitField<5, 1, u8> WEEKEVENTREG_OCEANSIDE_SPIDER_HOUSE_BUYER_MOVED_IN;
    BitField<6, 1, u8> WEEKEVENTREG_RECEIVED_OCEANSIDE_WALLET_UPGRADE;
    BitField<7, 1, u8> WEEKEVENTREG_OCEANSIDE_SPIDER_HOUSE_COLLECTED_REWARD;
  };

  union WeekEventReg14 {
    u8 raw;

    // PlayedMilkMinigame
    // Attempted Cremia Cart Ride
    BitField<0, 1, u8> WEEKEVENTREG_14_01;

    BitField<1, 1, u8> WEEKEVENTREG_14_02;
    BitField<2, 1, u8> WEEKEVENTREG_14_04;
    BitField<3, 1, u8> WEEKEVENTREG_DRANK_CHATEAU_ROMANI;
    BitField<4, 1, u8> WEEKEVENTREG_WON_DEKU_PLAYGROUND_DAY_1;
    BitField<5, 1, u8> WEEKEVENTREG_WON_DEKU_PLAYGROUND_DAY_2;
    BitField<6, 1, u8> WEEKEVENTREG_WON_DEKU_PLAYGROUND_DAY_3;
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_DEKU_PLAYGROUND_HEART_PIECE;
  };

  union WeekEventReg15 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_15_01;
    BitField<1, 1, u8> WEEKEVENTREG_15_02;
    BitField<2, 1, u8> WEEKEVENTREG_15_04;
    BitField<3, 1, u8> WEEKEVENTREG_15_08;
    BitField<4, 1, u8> WEEKEVENTREG_15_10;
    BitField<5, 1, u8> WEEKEVENTREG_15_20;
    BitField<6, 1, u8> WEEKEVENTREG_15_40;
    BitField<7, 1, u8> WEEKEVENTREG_15_80;
  };

  union WeekEventReg16 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_16_01;
    BitField<1, 1, u8> WEEKEVENTREG_16_02;
    BitField<2, 1, u8> WEEKEVENTREG_16_04;
    BitField<3, 1, u8> WEEKEVENTREG_16_08;
    BitField<4, 1, u8> WEEKEVENTREG_TALKED_KOUME_INJURED;
    BitField<5, 1, u8> WEEKEVENTREG_16_20;
    BitField<6, 1, u8> WEEKEVENTREG_16_40;
    BitField<7, 1, u8> WEEKEVENTREG_16_80;
  };

  union WeekEventReg17 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_TALKED_KOUME_KIOSK_EMPTY;
    BitField<1, 1, u8> WEEKEVENTREG_17_02;
    BitField<2, 1, u8> WEEKEVENTREG_17_04;
    BitField<3, 1, u8> WEEKEVENTREG_17_08;
    BitField<4, 1, u8> WEEKEVENTREG_17_10;
    BitField<5, 1, u8> WEEKEVENTREG_17_20;
    BitField<6, 1, u8> WEEKEVENTREG_17_40;
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_LAND_TITLE_DEED;
  };

  union WeekEventReg18 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_18_01;
    BitField<1, 1, u8> WEEKEVENTREG_18_02;
    BitField<2, 1, u8> WEEKEVENTREG_TALKED_CURIOSITY_SHOP_MAN_AS_GORON;
    BitField<3, 1, u8> WEEKEVENTREG_TALKED_CURIOSITY_SHOP_MAN_AS_ZORA;
    BitField<4, 1, u8> WEEKEVENTREG_TALKED_CURIOSITY_SHOP_MAN_AS_DEKU;
    BitField<5, 1, u8> WEEKEVENTREG_18_20;
    BitField<6, 1, u8> WEEKEVENTREG_18_40;

    // Player has Powder Keg purchasing privileges.
    BitField<7, 1, u8> WEEKEVENTREG_HAS_POWDERKEG_PRIVILEGES;
  };

  union WeekEventReg19 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_19_01;
    BitField<1, 1, u8> WEEKEVENTREG_19_02;
    BitField<2, 1, u8> WEEKEVENTREG_19_04;
    BitField<3, 1, u8> WEEKEVENTREG_19_08;
    BitField<4, 1, u8> WEEKEVENTREG_19_10;
    BitField<5, 1, u8> WEEKEVENTREG_19_20;
    BitField<6, 1, u8> WEEKEVENTREG_19_40;
    BitField<7, 1, u8> WEEKEVENTREG_19_80;
  };

  union WeekEventReg20 {
    u8 raw;

    // woodfall temple purification cutscene watched
    BitField<0, 1, u8> WEEKEVENTREG_CLEARED_WOODFALL_TEMPLE;

    BitField<1, 1, u8> WEEKEVENTREG_20_02;
    BitField<2, 1, u8> WEEKEVENTREG_20_04;
    BitField<3, 1, u8> WEEKEVENTREG_20_08;
    BitField<4, 1, u8> WEEKEVENTREG_20_10;
    BitField<5, 1, u8> WEEKEVENTREG_20_20;
    BitField<6, 1, u8> WEEKEVENTREG_20_40;
    BitField<7, 1, u8> WEEKEVENTREG_20_80;
  };

  union WeekEventReg21 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_21_01;
    BitField<1, 1, u8> WEEKEVENTREG_21_02;

    // Player has spoken to Goron Graveyard's gravemaker while in Goron form.
    BitField<2, 1, u8> WEEKEVENTREG_TALKED_GORON_GRAVEMAKER_AS_GORON;
    // Player has spoken to formerly frozen Goron outside Goron Graveyard.
    BitField<3, 1, u8> WEEKEVENTREG_TALKED_THAWED_GRAVEYARD_GORON;
    BitField<4, 1, u8> WEEKEVENTREG_21_10;
    // Player talked with Romani before the alien invasion and agreed to help her
    BitField<5, 1, u8> WEEKEVENTREG_PROMISED_TO_HELP_WITH_ALIENS;
    BitField<6, 1, u8> WEEKEVENTREG_21_40;
    BitField<7, 1, u8> WEEKEVENTREG_21_80;
  };

  union WeekEventReg22 {
    BitField<0, 1, u8> WEEKEVENTREG_22_01;
    BitField<1, 1, u8> WEEKEVENTREG_22_02;
    BitField<2, 1, u8> WEEKEVENTREG_22_04;
    BitField<3, 1, u8> WEEKEVENTREG_22_08;
    BitField<4, 1, u8> WEEKEVENTREG_22_10;
    BitField<5, 1, u8> WEEKEVENTREG_22_20;
    BitField<6, 1, u8> WEEKEVENTREG_22_40;
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_HONEY_AND_DARLING_HEART_PIECE;
  };

  union WeekEventReg23 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_23_01;
    BitField<1, 1, u8> WEEKEVENTREG_RECEIVED_GREAT_SPIN_ATTACK;
    BitField<2, 1, u8> WEEKEVENTREG_23_04;
    BitField<3, 1, u8> WEEKEVENTREG_23_08;
    BitField<4, 1, u8> WEEKEVENTREG_23_10;
    BitField<5, 1, u8> WEEKEVENTREG_23_20;
    BitField<6, 1, u8> WEEKEVENTREG_23_40;
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_BEAVER_RACE_BOTTLE;
  };

  union WeekEventReg24 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_24_01;
    BitField<1, 1, u8> WEEKEVENTREG_24_02;
    BitField<2, 1, u8> WEEKEVENTREG_24_04;
    BitField<3, 1, u8> WEEKEVENTREG_24_08;
    // The player has already talked as a Goron at least once to Goron elder
    BitField<4, 1, u8> WEEKEVENTREG_24_10;
    // The player has already talked as a non-Goron at least once
    BitField<5, 1, u8> WEEKEVENTREG_24_20;
    BitField<6, 1, u8> WEEKEVENTREG_24_40;
    // The player has talked to the Goron Child at least once
    BitField<7, 1, u8> WEEKEVENTREG_24_80;
  };

  union WeekEventReg25 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_RECEIVED_BEAVER_BROS_HEART_PIECE;
    BitField<1, 1, u8> WEEKEVENTREG_OATH_CUTSCENE_SUCCEEDED;
    BitField<2, 1, u8> WEEKEVENTREG_25_04;
    BitField<3, 1, u8> WEEKEVENTREG_BREMAN_MASK_USED;
    BitField<4, 1, u8> WEEKEVENTREG_25_10;
    BitField<5, 1, u8> WEEKEVENTREG_25_20;
    BitField<6, 1, u8> WEEKEVENTREG_25_40;
    BitField<7, 1, u8> WEEKEVENTREG_25_80;
  };

  union WeekEventReg26 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_26_01;
    BitField<1, 1, u8> WEEKEVENTREG_26_02;
    BitField<2, 1, u8> WEEKEVENTREG_26_04;
    BitField<3, 1, u8> WEEKEVENTREG_26_08;
    BitField<4, 1, u8> WEEKEVENTREG_26_10;
    BitField<5, 1, u8> WEEKEVENTREG_26_20;
    BitField<6, 1, u8> WEEKEVENTREG_26_40;
    BitField<7, 1, u8> WEEKEVENTREG_26_80;
  };

  union WeekEventReg27 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_27_01;
    BitField<1, 1, u8> WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_UPPER_CLOCKTOWN;
    BitField<2, 1, u8> WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_NORTH_CLOCKTOWN;
    BitField<3, 1, u8> WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_UPPER_CLOCKTOWN;
    BitField<4, 1, u8> WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_LOWER_CLOCKTOWN;
    BitField<5, 1, u8> WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_LOWER_CLOCKTOWN;
    BitField<6, 1, u8> WEEKEVENTREG_27_40;
    BitField<7, 1, u8> WEEKEVENTREG_27_80;
  };

  union WeekEventReg28 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_28_01;
    BitField<1, 1, u8> WEEKEVENTREG_28_02;
    BitField<2, 1, u8> WEEKEVENTREG_28_04;
    BitField<3, 1, u8> WEEKEVENTREG_28_08;
    BitField<4, 1, u8> WEEKEVENTREG_28_10;
    BitField<5, 1, u8> WEEKEVENTREG_28_20;
    BitField<6, 1, u8> WEEKEVENTREG_28_40;
    BitField<7, 1, u8> WEEKEVENTREG_28_80;
  };

  union WeekEventReg29 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_29_01;
    BitField<1, 1, u8> WEEKEVENTREG_29_02;
    BitField<2, 1, u8> WEEKEVENTREG_29_04;
    BitField<3, 1, u8> WEEKEVENTREG_29_08;
    BitField<4, 1, u8> WEEKEVENTREG_29_10;
    BitField<5, 1, u8> WEEKEVENTREG_29_20;
    BitField<6, 1, u8> WEEKEVENTREG_29_40;
    BitField<7, 1, u8> WEEKEVENTREG_29_80;
  };

  union WeekEventReg30 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_30_01;
    BitField<1, 1, u8> WEEKEVENTREG_30_02;
    BitField<2, 1, u8> WEEKEVENTREG_30_04;
    BitField<3, 1, u8> WEEKEVENTREG_30_08;
    BitField<4, 1, u8> WEEKEVENTREG_WORN_DEKU_MASK_ONCE;
    BitField<5, 1, u8> WEEKEVENTREG_WORN_GORON_MASK_ONCE;
    BitField<6, 1, u8> WEEKEVENTREG_WORN_ZORA_MASK_ONCE;
    BitField<7, 1, u8> WEEKEVENTREG_WORN_FIERCE_DEITY_MASK_ONCE;
  };

  union WeekEventReg31 {
    u8 raw;
    // Unconfirmed: "Tatl's Second Cycle Text?"
    BitField<2, 1, u8> WEEKEVENTREG_TATL_NOT_FINISHED_MOUNTAIN_TEXT;
    BitField<3, 1, u8> WEEKEVENTREG_TATL_NOT_FINISHED_OCEAN_TEXT;
    BitField<4, 1, u8> WEEKEVENTREG_TATL_GO_SOUTH_TEXT;
    BitField<5, 1, u8> WEEKEVENTREG_31_20;
    // Cremia asked the player to accompany her to town
    BitField<6, 1, u8> WEEKEVENTREG_31_40;
    // Player is playing the Milk Run
    BitField<7, 1, u8> WEEKEVENTREG_31_80;
  };

  union WeekEventReg32 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_RECEIVED_SEAHORSE_HEART_PIECE;
    BitField<1, 1, u8> WEEKEVENTREG_RECEIVED_SWAMP_SHOOTING_GALLERY_HEART_PIECE;
    BitField<2, 1, u8> WEEKEVENTREG_RECEIVED_TOWN_SHOOTING_GALLERY_HEART_PIECE;
    BitField<3, 1, u8> WEEKEVENTREG_32_08;
    BitField<4, 1, u8> WEEKEVENTREG_32_10;
    BitField<5, 1, u8> WEEKEVENTREG_32_20;
    // Woodfall Temple Frog Returned
    BitField<6, 1, u8> WEEKEVENTREG_32_40;
    // Great Bay Temple Frog Returned
    BitField<7, 1, u8> WEEKEVENTREG_32_80;
  };

  union WeekEventReg33 {
    u8 raw;

    // Southern Swamp Frog Returned
    BitField<0, 1, u8> WEEKEVENTREG_33_01;
    // Laundry Pool Frog Returned
    BitField<1, 1, u8> WEEKEVENTREG_33_02;
    BitField<2, 1, u8> WEEKEVENTREG_BOUGHT_CURIOSITY_SHOP_SPECIAL_ITEM;
    BitField<3, 1, u8> WEEKEVENTREG_RECOVERED_STOLEN_BOMB_BAG;
    BitField<4, 1, u8> WEEKEVENTREG_33_10;
    BitField<5, 1, u8> WEEKEVENTREG_33_20;
    BitField<6, 1, u8> WEEKEVENTREG_33_40;
    // Mountain village unfrozen
    BitField<7, 1, u8> WEEKEVENTREG_CLEARED_SNOWHEAD_TEMPLE;
  };

  union WeekEventReg34 {
    u8 raw;
    // Spoken to FROG_YELLOW
    BitField<0, 1, u8> WEEKEVENTREG_34_01;
    BitField<1, 1, u8> WEEKEVENTREG_34_02;
    BitField<2, 1, u8> WEEKEVENTREG_34_04;
    BitField<3, 1, u8> WEEKEVENTREG_TALKED_SWAMP_SPIDER_HOUSE_MAN;
    BitField<4, 1, u8> WEEKEVENTREG_34_10;
    BitField<5, 1, u8> WEEKEVENTREG_34_20;
    BitField<6, 1, u8> WEEKEVENTREG_RECEIVED_MASK_OF_TRUTH;
    // Cremia did Milk Run alone. Player didn't interact or didn't accept the ride
    BitField<7, 1, u8> WEEKEVENTREG_34_80;
  };

  union WeekEventReg35 {
    u8 raw;
    // Bought each possible map from Tingle
    BitField<0, 1, u8> WEEKEVENTREG_TINGLE_MAP_BOUGHT_CLOCK_TOWN;
    BitField<1, 1, u8> WEEKEVENTREG_TINGLE_MAP_BOUGHT_WOODFALL;
    BitField<2, 1, u8> WEEKEVENTREG_TINGLE_MAP_BOUGHT_SNOWHEAD;
    BitField<3, 1, u8> WEEKEVENTREG_TINGLE_MAP_BOUGHT_ROMANI_RANCH;
    BitField<4, 1, u8> WEEKEVENTREG_TINGLE_MAP_BOUGHT_GREAT_BAY;
    BitField<5, 1, u8> WEEKEVENTREG_TINGLE_MAP_BOUGHT_STONE_TOWER;
    BitField<6, 1, u8> WEEKEVENTREG_35_40;
    // Obtained Heart Piece from Five Frogs of the Frog Choir
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_FROG_CHOIR_HEART_PIECE;
  };

  union WeekEventReg36 {
    u8 raw;
    // Player has spoken to certain shrine gorons in the winter
    BitField<0, 1, u8> WEEKEVENTREG_36_01;
    BitField<1, 1, u8> WEEKEVENTREG_36_02;
    BitField<2, 1, u8> WEEKEVENTREG_36_04;
    BitField<3, 1, u8> WEEKEVENTREG_36_08;
    BitField<4, 1, u8> WEEKEVENTREG_36_10;
    BitField<5, 1, u8> WEEKEVENTREG_36_20;
    BitField<6, 1, u8> WEEKEVENTREG_36_40;
    BitField<7, 1, u8> WEEKEVENTREG_36_80;
  };

  union WeekEventReg37 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_37_01;
    BitField<1, 1, u8> WEEKEVENTREG_37_02;
    BitField<2, 1, u8> WEEKEVENTREG_37_04;
    BitField<3, 1, u8> WEEKEVENTREG_37_08;
    // Sets to 1 if the rock sirloin has spawned.
    BitField<4, 1, u8> WEEKEVENTREG_37_10;
    BitField<5, 1, u8> WEEKEVENTREG_37_20;
    BitField<6, 1, u8> WEEKEVENTREG_37_40;
    BitField<7, 1, u8> WEEKEVENTREG_37_80;
  };

  union WeekEventReg38 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_38_01;
    BitField<1, 1, u8> WEEKEVENTREG_38_02;
    BitField<2, 1, u8> WEEKEVENTREG_38_04;
    BitField<3, 1, u8> WEEKEVENTREG_38_08;
    BitField<4, 1, u8> WEEKEVENTREG_38_10;
    BitField<5, 1, u8> WEEKEVENTREG_38_20;
    BitField<6, 1, u8> WEEKEVENTREG_38_40;
    BitField<7, 1, u8> WEEKEVENTREG_38_80;
  };

  union WeekEventReg39 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_39_01;
    BitField<1, 1, u8> WEEKEVENTREG_39_02;
    BitField<2, 1, u8> WEEKEVENTREG_39_04;
    BitField<3, 1, u8> WEEKEVENTREG_39_08;
    BitField<4, 1, u8> WEEKEVENTREG_39_10;
    BitField<5, 1, u8> WEEKEVENTREG_RECEIVED_EVAN_HEART_PIECE;
    BitField<6, 1, u8> WEEKEVENTREG_39_40;
    BitField<7, 1, u8> WEEKEVENTREG_39_80;
  };

  union WeekEventReg40 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_40_01;
    BitField<1, 1, u8> WEEKEVENTREG_40_02;
    BitField<2, 1, u8> WEEKEVENTREG_40_04;
    BitField<3, 1, u8> WEEKEVENTREG_40_08;
    BitField<4, 1, u8> WEEKEVENTREG_40_10;
    BitField<5, 1, u8> WEEKEVENTREG_40_20;
    BitField<6, 1, u8> WEEKEVENTREG_40_40;
    BitField<7, 1, u8> WEEKEVENTREG_40_80;
  };

  union WeekEventReg41 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_41_01;
    BitField<1, 1, u8> WEEKEVENTREG_41_02;
    BitField<2, 1, u8> WEEKEVENTREG_41_04;
    BitField<3, 1, u8> WEEKEVENTREG_RECEIVED_GORON_RACE_BOTTLE;
    BitField<4, 1, u8> WEEKEVENTREG_41_10;
    BitField<5, 1, u8> WEEKEVENTREG_41_20;
    BitField<6, 1, u8> WEEKEVENTREG_41_40;
    BitField<7, 1, u8> WEEKEVENTREG_41_80;
  };
  // Used for storing the text ID offsets for the dogs in the Doggy Racetrack (56 entries)
  // The number of weekEventRegs used needs to be kept in sync with RACEDOG_COUNT in z_en_aob_01.h
  // PACK_WEEKEVENTREG_FLAG(42, 0x01) to PACK_WEEKEVENTREG_FLAG(48, 0x80)
  union WeekEventReg42 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_42_01;
    BitField<1, 1, u8> WEEKEVENTREG_42_02;
    BitField<2, 1, u8> WEEKEVENTREG_42_04;
    BitField<3, 1, u8> WEEKEVENTREG_42_08;
    BitField<4, 1, u8> WEEKEVENTREG_42_10;
    BitField<5, 1, u8> WEEKEVENTREG_42_20;
    BitField<6, 1, u8> WEEKEVENTREG_42_40;
    BitField<7, 1, u8> WEEKEVENTREG_42_80;
  };

  union WeekEventReg43 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_43_01;
    BitField<1, 1, u8> WEEKEVENTREG_43_02;
    BitField<2, 1, u8> WEEKEVENTREG_43_04;
    BitField<3, 1, u8> WEEKEVENTREG_43_08;
    BitField<4, 1, u8> WEEKEVENTREG_43_10;
    BitField<5, 1, u8> WEEKEVENTREG_43_20;
    BitField<6, 1, u8> WEEKEVENTREG_43_40;
    BitField<7, 1, u8> WEEKEVENTREG_43_80;
  };

  union WeekEventReg44 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_44_01;
    BitField<1, 1, u8> WEEKEVENTREG_44_02;
    BitField<2, 1, u8> WEEKEVENTREG_44_04;
    BitField<3, 1, u8> WEEKEVENTREG_44_08;
    BitField<4, 1, u8> WEEKEVENTREG_44_10;
    BitField<5, 1, u8> WEEKEVENTREG_44_20;
    BitField<6, 1, u8> WEEKEVENTREG_44_40;
    BitField<7, 1, u8> WEEKEVENTREG_44_80;
  };

  union WeekEventReg45 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_45_01;
    BitField<1, 1, u8> WEEKEVENTREG_45_02;
    BitField<2, 1, u8> WEEKEVENTREG_45_04;
    BitField<3, 1, u8> WEEKEVENTREG_45_08;
    BitField<4, 1, u8> WEEKEVENTREG_45_10;
    BitField<5, 1, u8> WEEKEVENTREG_45_20;
    BitField<6, 1, u8> WEEKEVENTREG_45_40;
    BitField<7, 1, u8> WEEKEVENTREG_45_80;
  };

  union WeekEventReg46 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_46_01;
    BitField<1, 1, u8> WEEKEVENTREG_46_02;
    BitField<2, 1, u8> WEEKEVENTREG_46_04;
    BitField<3, 1, u8> WEEKEVENTREG_46_08;
    BitField<4, 1, u8> WEEKEVENTREG_46_10;
    BitField<5, 1, u8> WEEKEVENTREG_46_20;
    BitField<6, 1, u8> WEEKEVENTREG_46_40;
    BitField<7, 1, u8> WEEKEVENTREG_46_80;
  };

  union WeekEventReg47 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_47_01;
    BitField<1, 1, u8> WEEKEVENTREG_47_02;
    BitField<2, 1, u8> WEEKEVENTREG_47_04;
    BitField<3, 1, u8> WEEKEVENTREG_47_08;
    BitField<4, 1, u8> WEEKEVENTREG_47_10;
    BitField<5, 1, u8> WEEKEVENTREG_47_20;
    BitField<6, 1, u8> WEEKEVENTREG_47_40;
    BitField<7, 1, u8> WEEKEVENTREG_47_80;
  };

  union WeekEventReg48 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_48_01;
    BitField<1, 1, u8> WEEKEVENTREG_48_02;
    BitField<2, 1, u8> WEEKEVENTREG_48_04;
    BitField<3, 1, u8> WEEKEVENTREG_48_08;
    BitField<4, 1, u8> WEEKEVENTREG_48_10;
    BitField<5, 1, u8> WEEKEVENTREG_48_20;
    BitField<6, 1, u8> WEEKEVENTREG_48_40;
    BitField<7, 1, u8> WEEKEVENTREG_48_80;
  };

  union WeekEventReg49 {
    u8 raw;

    BitField<0, 1, u8> WEEKEVENTREG_49_01;
    BitField<1, 1, u8> WEEKEVENTREG_49_02;
    BitField<2, 1, u8> WEEKEVENTREG_49_04;
    BitField<3, 1, u8> WEEKEVENTREG_49_08;
    BitField<4, 1, u8> WEEKEVENTREG_49_10;
    BitField<5, 1, u8> WEEKEVENTREG_49_20;
    BitField<6, 1, u8> WEEKEVENTREG_49_40;
    BitField<7, 1, u8> WEEKEVENTREG_49_80;
  };

  union WeekEventReg50 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_50_01;
    BitField<1, 1, u8> WEEKEVENTREG_50_02;
    BitField<2, 1, u8> WEEKEVENTREG_50_04;
    BitField<3, 1, u8> WEEKEVENTREG_PROMISED_MIDNIGHT_MEETING;
    BitField<4, 1, u8> WEEKEVENTREG_50_10;
    BitField<5, 1, u8> WEEKEVENTREG_HAD_MIDNIGHT_MEETING;
    BitField<6, 1, u8> WEEKEVENTREG_50_40;
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_PENDANT_OF_MEMORIES;
  };

  union WeekEventReg51 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_DELIVERED_PENDANT_OF_MEMORIES;
    BitField<1, 1, u8> WEEKEVENTREG_51_02;
    BitField<2, 1, u8> WEEKEVENTREG_51_04;
    BitField<3, 1, u8> WEEKEVENTREG_51_08;
    BitField<4, 1, u8> WEEKEVENTREG_51_10;
    BitField<5, 1, u8> WEEKEVENTREG_ESCAPED_SAKONS_HIDEOUT;
    // Set by Kafei
    BitField<6, 1, u8> WEEKEVENTREG_COUPLES_MASK_CUTSCENE_FINISHED;
    BitField<7, 1, u8> WEEKEVENTREG_51_80;
  };

  union WeekEventReg52 {
    u8 raw;
    // Protected Cremia
    BitField<0, 1, u8> WEEKEVENTREG_ESCORTED_CREMIA;
    // Lose Milk Run minigame
    BitField<1, 1, u8> WEEKEVENTREG_52_02;
    BitField<2, 1, u8> WEEKEVENTREG_52_04;
    BitField<3, 1, u8> WEEKEVENTREG_52_08;
    BitField<4, 1, u8> WEEKEVENTREG_52_10;
    BitField<5, 1, u8> WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE;
    BitField<6, 1, u8> WEEKEVENTREG_52_40;
    BitField<7, 1, u8> WEEKEVENTREG_52_80;
  };

  union WeekEventReg53 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_53_01;
    BitField<1, 1, u8> WEEKEVENTREG_RECEIVED_BUSINESS_SCRUB_HEART_PIECE;
    BitField<2, 1, u8> WEEKEVENTREG_53_04;
    BitField<3, 1, u8> WEEKEVENTREG_GAVE_KOTAKE_MUSHROOM;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_FREE_BLUE_POTION;
    BitField<5, 1, u8> WEEKEVENTREG_53_20;
    BitField<6, 1, u8> WEEKEVENTREG_53_40;
    BitField<7, 1, u8> WEEKEVENTREG_53_80;
  };

  union WeekEventReg54 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_54_01;
    BitField<1, 1, u8> WEEKEVENTREG_54_02;
    BitField<2, 1, u8> WEEKEVENTREG_54_04;
    BitField<3, 1, u8> WEEKEVENTREG_54_08;
    BitField<4, 1, u8> WEEKEVENTREG_TALKED_ROMANI_ON_NIGHT_1;
    BitField<5, 1, u8> WEEKEVENTREG_54_20;
    BitField<6, 1, u8> WEEKEVENTREG_RECEIVED_SPIRIT_HOUSE_HEART_PIECE;
    BitField<7, 1, u8> WEEKEVENTREG_54_80;
  };

  union WeekEventReg55 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_55_01;
    // Unconfirmed: "Link the Goron Claims His Reservation: 4:30 PM"
    BitField<1, 1, u8> WEEKEVENTREG_55_02;
    BitField<2, 1, u8> WEEKEVENTREG_TALKED_PART_TIMER_AS_GORON;
    BitField<3, 1, u8> WEEKEVENTREG_TALKED_PART_TIMER_AS_ZORA;
    BitField<4, 1, u8> WEEKEVENTREG_TALKED_PART_TIMER_AS_DEKU;
    BitField<5, 1, u8> WEEKEVENTREG_TALKED_ANJU_IN_LAUNDRY_POOL;
    BitField<6, 1, u8> WEEKEVENTREG_55_40;
    // Gyorg has been defeated
    BitField<7, 1, u8> WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE;
  };

  union WeekEventReg56 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_56_01;
    BitField<1, 1, u8> WEEKEVENTREG_RECEIVED_MARINE_RESEARCH_LAB_FISH_HEART_PIECE;
    BitField<2, 1, u8> WEEKEVENTREG_56_04;
    BitField<3, 1, u8> WEEKEVENTREG_56_08;
    BitField<4, 1, u8> WEEKEVENTREG_56_10;
    BitField<5, 1, u8> WEEKEVENTREG_56_20;
    BitField<6, 1, u8> WEEKEVENTREG_56_40;
    BitField<7, 1, u8> WEEKEVENTREG_56_80;
  };

  union WeekEventReg57 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_57_01;
    BitField<1, 1, u8> WEEKEVENTREG_57_02;
    BitField<2, 1, u8> WEEKEVENTREG_57_04;
    BitField<3, 1, u8> WEEKEVENTREG_57_08;
    BitField<4, 1, u8> WEEKEVENTREG_TALKED_ZORA_SHOPKEEPER_AS_HUMAN;
    BitField<5, 1, u8> WEEKEVENTREG_TALKED_ZORA_SHOPKEEPER_AS_DEKU;
    BitField<6, 1, u8> WEEKEVENTREG_TALKED_ZORA_SHOPKEEPER_AS_GORON;
    BitField<7, 1, u8> WEEKEVENTREG_TALKED_ZORA_SHOPKEEPER_AS_ZORA;
  };

  union WeekEventReg58 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_58_01;
    BitField<1, 1, u8> WEEKEVENTREG_58_02;
    BitField<2, 1, u8> WEEKEVENTREG_TALKED_GORON_SHOPKEEPER_AS_NON_GORON;
    BitField<3, 1, u8> WEEKEVENTREG_TALKED_GORON_SHOPKEEPER_AS_GORON;
    BitField<4, 1, u8> WEEKEVENTREG_TALKED_GORON_SHOPKEEPER_SPRING_AS_NON_GORON;
    BitField<5, 1, u8> WEEKEVENTREG_TALKED_GORON_SHOPKEEPER_SPRING_AS_GORON;
    BitField<6, 1, u8> WEEKEVENTREG_58_40;
    BitField<7, 1, u8> WEEKEVENTREG_58_80;
  };

  union WeekEventReg59 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_59_01;
    BitField<1, 1, u8> WEEKEVENTREG_59_02;
    // Unconfirmed: "Entered South Clock Town"
    BitField<2, 1, u8> WEEKEVENTREG_59_04;
    BitField<3, 1, u8> WEEKEVENTREG_RECEIVED_BANK_HEART_PIECE;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_SWAMP_SHOOTING_GALLERY_QUIVER_UPGRADE;
    BitField<5, 1, u8> WEEKEVENTREG_RECEIVED_TOWN_SHOOTING_GALLERY_QUIVER_UPGRADE;
    BitField<6, 1, u8> WEEKEVENTREG_59_40;
    BitField<7, 1, u8> WEEKEVENTREG_59_80;
  };

  union WeekEventReg60 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_60_01;
    BitField<1, 1, u8> WEEKEVENTREG_60_02;
    BitField<2, 1, u8> WEEKEVENTREG_60_04;
    BitField<3, 1, u8> WEEKEVENTREG_ATTENDED_MAYOR_MEETING;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_MAYOR_HEART_PIECE;
    BitField<5, 1, u8> WEEKEVENTREG_60_20;
    BitField<6, 1, u8> WEEKEVENTREG_TALKED_MAYOR_NIGHT_3;
    BitField<7, 1, u8> WEEKEVENTREG_60_80;
  };

  union WeekEventReg61 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_61_01;
    BitField<1, 1, u8> WEEKEVENTREG_61_02;
    BitField<2, 1, u8> WEEKEVENTREG_61_04;
    BitField<3, 1, u8> WEEKEVENTREG_61_08;
    BitField<4, 1, u8> WEEKEVENTREG_61_10;
    BitField<5, 1, u8> WEEKEVENTREG_61_20;
    BitField<6, 1, u8> WEEKEVENTREG_61_40;
    BitField<7, 1, u8> WEEKEVENTREG_61_80;
  };

  union WeekEventReg62 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_62_01;
    BitField<1, 1, u8> WEEKEVENTREG_62_02;
    BitField<2, 1, u8> WEEKEVENTREG_62_04;
    BitField<3, 1, u8> WEEKEVENTREG_62_08;
    BitField<4, 1, u8> WEEKEVENTREG_62_10;
    BitField<5, 1, u8> WEEKEVENTREG_62_20;
    BitField<6, 1, u8> WEEKEVENTREG_62_40;
    BitField<7, 1, u8> WEEKEVENTREG_62_80;
  };

  union WeekEventReg63 {
    u8 raw;
    // See `EnTimeTag_KickOut_WaitForTime` and `EnTimeTag_KickOut_WaitForTrigger`
    BitField<0, 1, u8> WEEKEVENTREG_KICKOUT_WAIT;
    // See `EnTimeTag_KickOut_WaitForTime` and `EnTimeTag_KickOut_WaitForTrigger`
    BitField<1, 1, u8> WEEKEVENTREG_KICKOUT_TIME_PASSED;
    BitField<2, 1, u8> WEEKEVENTREG_63_04;
    BitField<3, 1, u8> WEEKEVENTREG_63_08;
    BitField<4, 1, u8> WEEKEVENTREG_63_10;
    BitField<5, 1, u8> WEEKEVENTREG_RECEIVED_SWORDSMANS_SCHOOL_HEART_PIECE;
    BitField<6, 1, u8> WEEKEVENTREG_63_40;
    // Showed Couple's Mask at meeting
    BitField<7, 1, u8> WEEKEVENTREG_RESOLVED_MAYOR_MEETING;
  };

  union WeekEventReg64 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_64_01;
    BitField<1, 1, u8> WEEKEVENTREG_64_02;
    BitField<2, 1, u8> WEEKEVENTREG_64_04;
    //  0 - Zora, LOW_BIT - Deku, HIGH_BIT - Goron, LOW_BIT & HIGH_BIT - Human
    BitField<3, 1, u8> WEEKEVENTREG_TINGLE_RECOGNIZED_PLAYER_FORM_LOW_BIT;
    BitField<4, 1, u8> WEEKEVENTREG_TINGLE_RECOGNIZED_PLAYER_FORM_HIGH_BIT;
    BitField<5, 1, u8> WEEKEVENTREG_64_20;
    BitField<6, 1, u8> WEEKEVENTREG_64_40;
    BitField<7, 1, u8> WEEKEVENTREG_TALKED_DOGGY_RACETRACK_OWNER_DAY_1;
  };

  union WeekEventReg65 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_TALKED_DOGGY_RACETRACK_OWNER_NIGHT_1;
    BitField<1, 1, u8> WEEKEVENTREG_TALKED_DOGGY_RACETRACK_OWNER_DAY_2;
    BitField<2, 1, u8> WEEKEVENTREG_TALKED_DOGGY_RACETRACK_OWNER_NIGHT_2;
    BitField<3, 1, u8> WEEKEVENTREG_TALKED_DOGGY_RACETRACK_OWNER_DAY_3;
    BitField<4, 1, u8> WEEKEVENTREG_TALKED_DOGGY_RACETRACK_OWNER_NIGHT_3;
    BitField<5, 1, u8> WEEKEVENTREG_65_20;
    BitField<6, 1, u8> WEEKEVENTREG_65_40;
    BitField<7, 1, u8> WEEKEVENTREG_65_80;
  };

  union WeekEventReg66 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_66_01;
    BitField<1, 1, u8> WEEKEVENTREG_66_02;
    BitField<2, 1, u8> WEEKEVENTREG_66_04;
    BitField<3, 1, u8> WEEKEVENTREG_66_08;
    BitField<4, 1, u8> WEEKEVENTREG_66_10;
    BitField<5, 1, u8> WEEKEVENTREG_66_20;
    BitField<6, 1, u8> WEEKEVENTREG_66_40;
    BitField<7, 1, u8> WEEKEVENTREG_66_80;
  };

  union WeekEventReg67 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_67_01;
    BitField<1, 1, u8> WEEKEVENTREG_67_02;
    BitField<2, 1, u8> WEEKEVENTREG_67_04;
    BitField<3, 1, u8> WEEKEVENTREG_67_08;
    BitField<4, 1, u8> WEEKEVENTREG_67_10;
    BitField<5, 1, u8> WEEKEVENTREG_67_20;
    BitField<6, 1, u8> WEEKEVENTREG_67_40;
    BitField<7, 1, u8> WEEKEVENTREG_67_80;
  };

  union WeekEventReg68 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_68_01;
    BitField<1, 1, u8> WEEKEVENTREG_68_02;
    BitField<2, 1, u8> WEEKEVENTREG_68_04;
    BitField<3, 1, u8> WEEKEVENTREG_68_08;
    BitField<4, 1, u8> WEEKEVENTREG_68_10;
    BitField<5, 1, u8> WEEKEVENTREG_68_20;
    BitField<6, 1, u8> WEEKEVENTREG_68_40;
    BitField<7, 1, u8> WEEKEVENTREG_68_80;
  };

  union WeekEventReg69 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_69_01;
    BitField<1, 1, u8> WEEKEVENTREG_69_02;
    BitField<2, 1, u8> WEEKEVENTREG_69_04;
    BitField<3, 1, u8> WEEKEVENTREG_69_08;
    BitField<4, 1, u8> WEEKEVENTREG_69_10;
    BitField<5, 1, u8> WEEKEVENTREG_69_20;
    BitField<6, 1, u8> WEEKEVENTREG_69_40;
    BitField<7, 1, u8> WEEKEVENTREG_69_80;
  };

  union WeekEventReg70 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_70_01;
    BitField<1, 1, u8> WEEKEVENTREG_70_02;
    BitField<2, 1, u8> WEEKEVENTREG_70_04;
    BitField<3, 1, u8> WEEKEVENTREG_70_08;
    BitField<4, 1, u8> WEEKEVENTREG_70_10;
    BitField<5, 1, u8> WEEKEVENTREG_70_20;
    BitField<6, 1, u8> WEEKEVENTREG_70_40;
    BitField<7, 1, u8> WEEKEVENTREG_70_80;
  };

  union WeekEventReg71 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_71_01;
    BitField<1, 1, u8> WEEKEVENTREG_71_02;
    BitField<2, 1, u8> WEEKEVENTREG_71_04;
    BitField<3, 1, u8> WEEKEVENTREG_71_08;
    BitField<4, 1, u8> WEEKEVENTREG_71_10;
    BitField<5, 1, u8> WEEKEVENTREG_71_20;
    BitField<6, 1, u8> WEEKEVENTREG_71_40;
    BitField<7, 1, u8> WEEKEVENTREG_71_80;
  };

  union WeekEventReg72 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_72_01;
    BitField<1, 1, u8> WEEKEVENTREG_72_02;
    BitField<2, 1, u8> WEEKEVENTREG_72_04;
    BitField<3, 1, u8> WEEKEVENTREG_72_08;
    BitField<4, 1, u8> WEEKEVENTREG_72_10;
    BitField<5, 1, u8> WEEKEVENTREG_72_20;
    BitField<6, 1, u8> WEEKEVENTREG_72_40;
    BitField<7, 1, u8> WEEKEVENTREG_72_80;
  };

  union WeekEventReg73 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_73_01;
    BitField<1, 1, u8> WEEKEVENTREG_73_02;
    BitField<2, 1, u8> WEEKEVENTREG_73_04;
    BitField<3, 1, u8> WEEKEVENTREG_73_08;
    // Unconfirmed: "Bombers Hide & Seek started on Day 1?"
    BitField<4, 1, u8> WEEKEVENTREG_73_10;
    BitField<5, 1, u8> WEEKEVENTREG_73_20;
    BitField<6, 1, u8> WEEKEVENTREG_73_40;
    BitField<7, 1, u8> WEEKEVENTREG_73_80;
  };

  union WeekEventReg74 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_74_01;
    BitField<1, 1, u8> WEEKEVENTREG_74_02;
    BitField<2, 1, u8> WEEKEVENTREG_74_04;
    BitField<3, 1, u8> WEEKEVENTREG_74_08;
    BitField<4, 1, u8> WEEKEVENTREG_74_10;
    BitField<5, 1, u8> WEEKEVENTREG_74_20;
    BitField<6, 1, u8> WEEKEVENTREG_74_40;
    BitField<7, 1, u8> WEEKEVENTREG_74_80;
  };

  union WeekEventReg75 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_75_01;
    BitField<1, 1, u8> WEEKEVENTREG_75_02;
    BitField<2, 1, u8> WEEKEVENTREG_75_04;
    BitField<3, 1, u8> WEEKEVENTREG_75_08;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_ROOM_KEY;
    BitField<5, 1, u8> WEEKEVENTREG_75_20;
    BitField<6, 1, u8> WEEKEVENTREG_75_40;
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_ROSA_SISTERS_HEART_PIECE;
  };

  union WeekEventReg76 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_76_01;
    BitField<1, 1, u8> WEEKEVENTREG_76_02;
    BitField<2, 1, u8> WEEKEVENTREG_76_04;
    BitField<3, 1, u8> WEEKEVENTREG_76_08;
    BitField<4, 1, u8> WEEKEVENTREG_76_10;
    BitField<5, 1, u8> WEEKEVENTREG_76_20;
    BitField<6, 1, u8> WEEKEVENTREG_76_40;
    BitField<7, 1, u8> WEEKEVENTREG_76_80;
  };

  union WeekEventReg77 {
    // Grotto stone bitflags may exist here.
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_RECEIVED_POSTMAN_COUNTING_GAME_HEART_PIECE;
    BitField<1, 1, u8> WEEKEVENTREG_77_02;
    BitField<2, 1, u8> WEEKEVENTREG_77_04;
    BitField<3, 1, u8> WEEKEVENTREG_77_08;
    BitField<4, 1, u8> WEEKEVENTREG_77_10;
    BitField<5, 1, u8> WEEKEVENTREG_77_20;
    BitField<6, 1, u8> WEEKEVENTREG_77_40;
    // The player has heard the Goron Shrine cheer as a Goron at least once.
    BitField<7, 1, u8> WEEKEVENTREG_77_80;
  };

  union WeekEventReg78 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_78_01;
    BitField<1, 1, u8> WEEKEVENTREG_78_02;
    BitField<2, 1, u8> WEEKEVENTREG_78_04;
    BitField<3, 1, u8> WEEKEVENTREG_78_08;
    BitField<4, 1, u8> WEEKEVENTREG_78_10;
    BitField<5, 1, u8> WEEKEVENTREG_78_20;
    BitField<6, 1, u8> WEEKEVENTREG_78_40;
    BitField<7, 1, u8> WEEKEVENTREG_78_80;
  };

  union WeekEventReg79 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_79_01;
    BitField<1, 1, u8> WEEKEVENTREG_79_02;
    BitField<2, 1, u8> WEEKEVENTREG_79_04;
    // removes sacrecrow from shop.
    BitField<3, 1, u8> WEEKEVENTREG_79_08;
    BitField<4, 1, u8> WEEKEVENTREG_79_10;
    BitField<5, 1, u8> WEEKEVENTREG_79_20;
    BitField<6, 1, u8> WEEKEVENTREG_SAKON_DEAD;
    BitField<7, 1, u8> WEEKEVENTREG_RECEIVED_KEATON_HEART_PIECE;
  };

  union WeekEventReg80 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_80_01;
    BitField<1, 1, u8> WEEKEVENTREG_80_02;
    BitField<2, 1, u8> WEEKEVENTREG_80_04;
    // Aveil has spotted Player
    BitField<3, 1, u8> WEEKEVENTREG_80_08;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_PRIORITY_MAIL;
    BitField<5, 1, u8> WEEKEVENTREG_80_20;
    BitField<6, 1, u8> WEEKEVENTREG_80_40;
    BitField<7, 1, u8> WEEKEVENTREG_80_80;
  };

  union WeekEventReg81 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_81_01;
    BitField<1, 1, u8> WEEKEVENTREG_81_02;
    BitField<2, 1, u8> WEEKEVENTREG_81_04;
    BitField<3, 1, u8> WEEKEVENTREG_81_08;
    BitField<4, 1, u8> WEEKEVENTREG_81_10;
    BitField<5, 1, u8> WEEKEVENTREG_81_20;
    BitField<6, 1, u8> WEEKEVENTREG_81_40;
    BitField<7, 1, u8> WEEKEVENTREG_81_80;
  };

  union WeekEventReg82 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_82_01;
    BitField<1, 1, u8> WEEKEVENTREG_82_02;
    // check if already healed Kamaro the Dancing Ghost
    BitField<2, 1, u8> WEEKEVENTREG_82_04;
    // Related to Swordsman's log minigame
    BitField<3, 1, u8> WEEKEVENTREG_82_08;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_FISHERMANS_JUMPING_GAME_HEART_PIECE;
    BitField<5, 1, u8> WEEKEVENTREG_82_20;
    BitField<6, 1, u8> WEEKEVENTREG_82_40;
    BitField<7, 1, u8> WEEKEVENTREG_82_80;
  };

  union WeekEventReg83 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_83_01;
    // Knocked the Gerudo beehive down
    BitField<1, 1, u8> WEEKEVENTREG_83_02;
    BitField<2, 1, u8> WEEKEVENTREG_83_04;
    // Used for loginc in CanUseItem.
    BitField<3, 1, u8> WEEKEVENTREG_83_08;
    BitField<4, 1, u8> WEEKEVENTREG_83_10;
    BitField<5, 1, u8> WEEKEVENTREG_83_20;
    BitField<6, 1, u8> WEEKEVENTREG_83_40;
    BitField<7, 1, u8> WEEKEVENTREG_83_80;
  };

  union WeekEventReg84 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_84_01;
    BitField<1, 1, u8> WEEKEVENTREG_84_02;
    BitField<2, 1, u8> WEEKEVENTREG_84_04;
    BitField<3, 1, u8> WEEKEVENTREG_84_08;
    BitField<4, 1, u8> WEEKEVENTREG_84_10;
    // Also related to moon child
    BitField<5, 1, u8> WEEKEVENTREG_84_20;
    BitField<6, 1, u8> WEEKEVENTREG_RECEIVED_RED_POTION_FOR_KOUME;
    BitField<7, 1, u8> WEEKEVENTREG_84_80;
  };

  union WeekEventReg85 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_85_01;
    // Unconfirmed: "Bombers Hide & Seek in Progress"
    BitField<1, 1, u8> WEEKEVENTREG_85_02;
    BitField<2, 1, u8> WEEKEVENTREG_85_04;
    // but is unable to do so since all bottles are full.
    BitField<3, 1, u8> WEEKEVENTREG_FAILED_RECEIVED_RED_POTION_FOR_KOUME_SHOP;
    BitField<4, 1, u8> WEEKEVENTREG_FAILED_RECEIVED_RED_POTION_FOR_KOUME_WOODS;
    BitField<5, 1, u8> WEEKEVENTREG_85_20;
    BitField<6, 1, u8> WEEKEVENTREG_85_40;
    // Unconfirmed: "Postman showing priority mail to Madame"
    BitField<7, 1, u8> WEEKEVENTREG_85_80;
  };

  union WeekEventReg86 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_86_01;
    BitField<1, 1, u8> WEEKEVENTREG_86_02;
    BitField<2, 1, u8> WEEKEVENTREG_86_04;
    BitField<3, 1, u8> WEEKEVENTREG_LISTENED_ANJU_POSTMAN_CONVERSATION;
    BitField<4, 1, u8> WEEKEVENTREG_86_10;
    BitField<5, 1, u8> WEEKEVENTREG_86_20;
    BitField<6, 1, u8> WEEKEVENTREG_86_40;
    BitField<7, 1, u8> WEEKEVENTREG_86_80;
  };

  union WeekEventReg87 {
    u8 raw;
    // Currently talking to a cow using the voice recognition unit
    BitField<0, 1, u8> WEEKEVENTREG_TALKING_TO_COW_WITH_VOICE;
    // Set by Anju
    BitField<1, 1, u8> WEEKEVENTREG_COUPLES_MASK_CUTSCENE_STARTED;
    BitField<2, 1, u8> WEEKEVENTREG_87_04;
    BitField<3, 1, u8> WEEKEVENTREG_87_08;
    BitField<4, 1, u8> WEEKEVENTREG_TATL_GO_NORTH_DIALOGUE_SPOKEN;
    BitField<5, 1, u8> WEEKEVENTREG_TATL_GO_WEST_DIALOGUE_SPOKEN;
    BitField<6, 1, u8> WEEKEVENTREG_TATL_GO_EAST_DIALOGUE_SPOKEN;
    BitField<7, 1, u8> WEEKEVENTREG_TATL_GO_TO_MOON_DIALOGUE_SPOKEN;
  };

  union WeekEventReg88 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_88_01;
    BitField<1, 1, u8> WEEKEVENTREG_88_02;
    BitField<2, 1, u8> WEEKEVENTREG_88_04;
    BitField<3, 1, u8> WEEKEVENTREG_88_08;
    BitField<4, 1, u8> WEEKEVENTREG_MIKAU_PUSHED_TO_SHORE;
    BitField<5, 1, u8> WEEKEVENTREG_88_20;
    // Goron shrine Gatekeeper has opened shrine.
    BitField<6, 1, u8> WEEKEVENTREG_GATEKEEPER_OPENED_GORON_SHRINE;
    // Goron shrine Gatekeeper has opened shrine for player in Human form.
    BitField<7, 1, u8> WEEKEVENTREG_GATEKEEPER_OPENED_GORON_SHRINE_FOR_HUMAN;
  };

  union WeekEventReg89 {
    u8 raw;
    // Goron shrine Gatekeeper has opened shrine for player in Deku form.
    BitField<0, 1, u8> WEEKEVENTREG_GATEKEEPER_OPENED_GORON_SHRINE_FOR_DEKU;
    // Goron shrine Gatekeeper has opened shrine for player in Zora form.
    BitField<1, 1, u8> WEEKEVENTREG_GATEKEEPER_OPENED_GORON_SHRINE_FOR_ZORA;
    // Goron shrine Gatekeeper has opened shrine for player in Goron form.
    BitField<2, 1, u8> WEEKEVENTREG_GATEKEEPER_OPENED_GORON_SHRINE_FOR_GORON;
    // Unconfirmed: "Postman has delivered priority mail"
    BitField<3, 1, u8> WEEKEVENTREG_89_08;
    // If the player isn't in the ranch when this happens, then this weekeventreg will remain unset.
    BitField<4, 1, u8> WEEKEVENTREG_FAILED_TO_DEFEND_AGAINST_ALIENS;
    BitField<5, 1, u8> WEEKEVENTREG_89_20;
    // Unconfirmed: "Postman is about to flee"
    BitField<6, 1, u8> WEEKEVENTREG_89_40;
    BitField<7, 1, u8> WEEKEVENTREG_89_80;
  };

  union WeekEventReg90 {
    u8 raw;
    // Unconfirmed: "Postman fleeing town"
    BitField<0, 1, u8> WEEKEVENTREG_90_01;
    BitField<1, 1, u8> WEEKEVENTREG_90_02;
    BitField<2, 1, u8> WEEKEVENTREG_90_04;
    BitField<3, 1, u8> WEEKEVENTREG_90_08;
    BitField<4, 1, u8> WEEKEVENTREG_RECEIVED_GOSSIP_STONE_GROTTO_HEART_PIECE;
    // Related to Fishermans's jumping minigame
    BitField<5, 1, u8> WEEKEVENTREG_90_20;
    BitField<6, 1, u8> WEEKEVENTREG_90_40;
    BitField<7, 1, u8> WEEKEVENTREG_90_80;
  };

  union WeekEventReg91 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_91_01;
    BitField<1, 1, u8> WEEKEVENTREG_91_02;
    // Mikau Dialog flags may exist here.
    BitField<2, 1, u8> WEEKEVENTREG_91_04;
    BitField<3, 1, u8> WEEKEVENTREG_91_08;
    BitField<4, 1, u8> WEEKEVENTREG_91_10;
    BitField<5, 1, u8> WEEKEVENTREG_91_20;
    BitField<6, 1, u8> WEEKEVENTREG_91_40;
    BitField<7, 1, u8> WEEKEVENTREG_91_80;
  };

  union WeekEventReg92 {
    u8 raw;
    // HORSE_RACE_STATE (3 entries)
    BitField<0, 1, u8> WEEKEVENTREG_92_01;
    BitField<1, 1, u8> WEEKEVENTREG_92_02;
    BitField<2, 1, u8> WEEKEVENTREG_92_04;

    BitField<3, 1, u8> WEEKEVENTREG_92_08;
    BitField<4, 1, u8> WEEKEVENTREG_92_10;
    BitField<5, 1, u8> WEEKEVENTREG_92_20;
    BitField<6, 1, u8> WEEKEVENTREG_92_40;
    BitField<7, 1, u8> WEEKEVENTREG_92_80;
  };

  union WeekEventReg93 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_93_01;
    BitField<1, 1, u8> WEEKEVENTREG_93_02;
    BitField<2, 1, u8> WEEKEVENTREG_CALLED_GIANTS_ON_ROOFTOP_ONCE;
    BitField<3, 1, u8> WEEKEVENTREG_93_08;
    BitField<4, 1, u8> WEEKEVENTREG_93_10;
    BitField<5, 1, u8> WEEKEVENTREG_93_20;
    BitField<6, 1, u8> WEEKEVENTREG_93_40;
    BitField<7, 1, u8> WEEKEVENTREG_93_80;
  };

  union WeekEventReg94 {
    u8 raw;
    // Song of healing talked to actor flags maybe
    BitField<0, 1, u8> WEEKEVENTREG_94_01;
    BitField<1, 1, u8> WEEKEVENTREG_94_02;
    BitField<2, 1, u8> WEEKEVENTREG_94_04;
    BitField<3, 1, u8> WEEKEVENTREG_94_08;
    BitField<4, 1, u8> WEEKEVENTREG_94_10;
    BitField<5, 1, u8> WEEKEVENTREG_94_20;
    BitField<6, 1, u8> WEEKEVENTREG_94_40;
    BitField<7, 1, u8> WEEKEVENTREG_94_80;
  };

  union WeekEventReg95 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_95_01;
    BitField<1, 1, u8> WEEKEVENTREG_95_02;
    BitField<2, 1, u8> WEEKEVENTREG_95_04;
    BitField<3, 1, u8> WEEKEVENTREG_95_08;
    BitField<4, 1, u8> WEEKEVENTREG_95_10;
    BitField<5, 1, u8> WEEKEVENTREG_95_20;
    BitField<6, 1, u8> WEEKEVENTREG_95_40;
    BitField<7, 1, u8> WEEKEVENTREG_95_80;
  };

  union WeekEventReg96 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_96_01;
    BitField<1, 1, u8> WEEKEVENTREG_96_02;
    BitField<2, 1, u8> WEEKEVENTREG_96_04;
    BitField<3, 1, u8> WEEKEVENTREG_96_08;
    BitField<4, 1, u8> WEEKEVENTREG_96_10;
    BitField<5, 1, u8> WEEKEVENTREG_96_20;
    BitField<6, 1, u8> WEEKEVENTREG_96_40;
    BitField<7, 1, u8> WEEKEVENTREG_96_80;
  };

  union WeekEventReg97 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_97_01;
    BitField<1, 1, u8> WEEKEVENTREG_97_02;
    BitField<2, 1, u8> WEEKEVENTREG_97_04;
    BitField<3, 1, u8> WEEKEVENTREG_97_08;
    BitField<4, 1, u8> WEEKEVENTREG_97_10;
    BitField<5, 1, u8> WEEKEVENTREG_97_20;
    BitField<6, 1, u8> WEEKEVENTREG_97_40;
    BitField<7, 1, u8> WEEKEVENTREG_97_80;
  };

  union WeekEventReg98 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_98_01;
    BitField<1, 1, u8> WEEKEVENTREG_98_02;
    BitField<2, 1, u8> WEEKEVENTREG_98_04;
    BitField<3, 1, u8> WEEKEVENTREG_98_08;
    BitField<4, 1, u8> WEEKEVENTREG_98_10;
    BitField<5, 1, u8> WEEKEVENTREG_98_20;
    BitField<6, 1, u8> WEEKEVENTREG_98_40;
    BitField<7, 1, u8> WEEKEVENTREG_98_80;
  };

  union WeekEventReg99 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_99_01;
    BitField<1, 1, u8> WEEKEVENTREG_99_02;
    BitField<2, 1, u8> WEEKEVENTREG_99_04;
    BitField<3, 1, u8> WEEKEVENTREG_99_08;
    BitField<4, 1, u8> WEEKEVENTREG_99_10;
    BitField<5, 1, u8> WEEKEVENTREG_99_20;
    BitField<6, 1, u8> WEEKEVENTREG_99_40;
    BitField<7, 1, u8> WEEKEVENTREG_99_80;
  };

  union WeekEventReg100 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_100_01;
    BitField<1, 1, u8> WEEKEVENTREG_100_02;
    BitField<2, 1, u8> WEEKEVENTREG_100_04;
    BitField<3, 1, u8> WEEKEVENTREG_100_08;
    BitField<4, 1, u8> WEEKEVENTREG_100_10;
    BitField<5, 1, u8> WEEKEVENTREG_100_20;
    BitField<6, 1, u8> WEEKEVENTREG_100_40;
    BitField<7, 1, u8> WEEKEVENTREG_100_80;
  };

  union WeekEventReg101 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_101_01;
    BitField<1, 1, u8> WEEKEVENTREG_101_02;
    BitField<2, 1, u8> WEEKEVENTREG_101_04;
    BitField<3, 1, u8> WEEKEVENTREG_101_08;
    BitField<4, 1, u8> WEEKEVENTREG_101_10;
    BitField<5, 1, u8> WEEKEVENTREG_101_20;
    BitField<6, 1, u8> WEEKEVENTREG_101_40;
    BitField<7, 1, u8> WEEKEVENTREG_101_80;
  };

  union WeekEventReg102 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_102_01;
    BitField<1, 1, u8> WEEKEVENTREG_102_02;
    BitField<2, 1, u8> WEEKEVENTREG_102_04;
    BitField<3, 1, u8> WEEKEVENTREG_102_08;
    BitField<4, 1, u8> WEEKEVENTREG_102_10;
    BitField<5, 1, u8> WEEKEVENTREG_102_20;
    BitField<6, 1, u8> WEEKEVENTREG_102_40;
    BitField<7, 1, u8> WEEKEVENTREG_102_80;
  };

  union WeekEventReg103 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_103_01;
    BitField<1, 1, u8> WEEKEVENTREG_103_02;
    BitField<2, 1, u8> WEEKEVENTREG_103_04;
    BitField<3, 1, u8> WEEKEVENTREG_103_08;
    BitField<4, 1, u8> WEEKEVENTREG_103_10;
    BitField<5, 1, u8> WEEKEVENTREG_103_20;
    BitField<6, 1, u8> WEEKEVENTREG_103_40;
    BitField<7, 1, u8> WEEKEVENTREG_103_80;
  };

  union WeekEventReg104 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_104_01;
    BitField<1, 1, u8> WEEKEVENTREG_104_02;
    BitField<2, 1, u8> WEEKEVENTREG_104_04;
    BitField<3, 1, u8> WEEKEVENTREG_104_08;
    BitField<4, 1, u8> WEEKEVENTREG_104_10;
    BitField<5, 1, u8> WEEKEVENTREG_104_20;
    BitField<6, 1, u8> WEEKEVENTREG_104_40;
    BitField<7, 1, u8> WEEKEVENTREG_104_80;
  };

  union WeekEventReg105 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_105_01;
    BitField<1, 1, u8> WEEKEVENTREG_105_02;
    BitField<2, 1, u8> WEEKEVENTREG_105_04;
    BitField<3, 1, u8> WEEKEVENTREG_105_08;
    BitField<4, 1, u8> WEEKEVENTREG_105_10;
    BitField<5, 1, u8> WEEKEVENTREG_105_20;
    BitField<6, 1, u8> WEEKEVENTREG_105_40;
    BitField<7, 1, u8> WEEKEVENTREG_105_80;
  };

  union WeekEventReg106 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_106_01;
    BitField<1, 1, u8> WEEKEVENTREG_106_02;
    BitField<2, 1, u8> WEEKEVENTREG_106_04;
    BitField<3, 1, u8> WEEKEVENTREG_106_08;
    BitField<4, 1, u8> WEEKEVENTREG_106_10;
    BitField<5, 1, u8> WEEKEVENTREG_106_20;
    BitField<6, 1, u8> WEEKEVENTREG_106_40;
    BitField<7, 1, u8> WEEKEVENTREG_106_80;
  };

  union WeekEventReg107 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_107_01;
    BitField<1, 1, u8> WEEKEVENTREG_107_02;
    BitField<2, 1, u8> WEEKEVENTREG_107_04;
    BitField<3, 1, u8> WEEKEVENTREG_107_08;
    BitField<4, 1, u8> WEEKEVENTREG_107_10;
    BitField<5, 1, u8> WEEKEVENTREG_107_20;
    BitField<6, 1, u8> WEEKEVENTREG_107_40;
    BitField<7, 1, u8> WEEKEVENTREG_107_80;
  };

  union WeekEventReg108 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_108_01;
    BitField<1, 1, u8> WEEKEVENTREG_108_02;
    BitField<2, 1, u8> WEEKEVENTREG_108_04;
    BitField<3, 1, u8> WEEKEVENTREG_108_08;
    BitField<4, 1, u8> WEEKEVENTREG_108_10;
    BitField<5, 1, u8> WEEKEVENTREG_108_20;
    BitField<6, 1, u8> WEEKEVENTREG_108_40;
    BitField<7, 1, u8> WEEKEVENTREG_108_80;
  };

  union WeekEventReg109 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_109_01;
    BitField<1, 1, u8> WEEKEVENTREG_109_02;
    BitField<2, 1, u8> WEEKEVENTREG_109_04;
    BitField<3, 1, u8> WEEKEVENTREG_109_08;
    BitField<4, 1, u8> WEEKEVENTREG_109_10;
    BitField<5, 1, u8> WEEKEVENTREG_109_20;
    BitField<6, 1, u8> WEEKEVENTREG_109_40;
    BitField<7, 1, u8> WEEKEVENTREG_109_80;
  };

  union WeekEventReg110 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_110_01;
    BitField<1, 1, u8> WEEKEVENTREG_110_02;
    BitField<2, 1, u8> WEEKEVENTREG_110_04;
    BitField<3, 1, u8> WEEKEVENTREG_110_08;
    BitField<4, 1, u8> WEEKEVENTREG_110_10;
    BitField<5, 1, u8> WEEKEVENTREG_110_20;
    BitField<6, 1, u8> WEEKEVENTREG_110_40;
    BitField<7, 1, u8> WEEKEVENTREG_110_80;
  };

  union WeekEventReg111 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_111_01;
    BitField<1, 1, u8> WEEKEVENTREG_111_02;
    BitField<2, 1, u8> WEEKEVENTREG_111_04;
    BitField<3, 1, u8> WEEKEVENTREG_111_08;
    BitField<4, 1, u8> WEEKEVENTREG_111_10;
    BitField<5, 1, u8> WEEKEVENTREG_111_20;
    BitField<6, 1, u8> WEEKEVENTREG_111_40;
    BitField<7, 1, u8> WEEKEVENTREG_111_80;
  };

  union WeekEventReg112 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_112_01;
    BitField<1, 1, u8> WEEKEVENTREG_112_02;
    BitField<2, 1, u8> WEEKEVENTREG_112_04;
    BitField<3, 1, u8> WEEKEVENTREG_112_08;
    BitField<4, 1, u8> WEEKEVENTREG_112_10;
    BitField<5, 1, u8> WEEKEVENTREG_112_20;
    BitField<6, 1, u8> WEEKEVENTREG_112_40;
    BitField<7, 1, u8> WEEKEVENTREG_112_80;
  };

  union WeekEventReg113 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_113_01;
    BitField<1, 1, u8> WEEKEVENTREG_113_02;
    BitField<2, 1, u8> WEEKEVENTREG_113_04;
    BitField<3, 1, u8> WEEKEVENTREG_113_08;
    BitField<4, 1, u8> WEEKEVENTREG_113_10;
    BitField<5, 1, u8> WEEKEVENTREG_113_20;
    BitField<6, 1, u8> WEEKEVENTREG_113_40;
    BitField<7, 1, u8> WEEKEVENTREG_113_80;
  };

  union WeekEventReg114 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_114_01;
    BitField<1, 1, u8> WEEKEVENTREG_114_02;
    BitField<2, 1, u8> WEEKEVENTREG_114_04;
    BitField<3, 1, u8> WEEKEVENTREG_114_08;
    BitField<4, 1, u8> WEEKEVENTREG_114_10;
    BitField<5, 1, u8> WEEKEVENTREG_114_20;
    BitField<6, 1, u8> WEEKEVENTREG_114_40;
    BitField<7, 1, u8> WEEKEVENTREG_114_80;
  };

  union WeekEventReg115 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_115_01;
    BitField<1, 1, u8> WEEKEVENTREG_115_02;
    BitField<2, 1, u8> WEEKEVENTREG_115_04;
    BitField<3, 1, u8> WEEKEVENTREG_115_08;
    BitField<4, 1, u8> WEEKEVENTREG_115_10;
    BitField<5, 1, u8> WEEKEVENTREG_115_20;
    BitField<6, 1, u8> WEEKEVENTREG_115_40;
    BitField<7, 1, u8> WEEKEVENTREG_115_80;
  };

  union WeekEventReg116 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_116_01;
    BitField<1, 1, u8> WEEKEVENTREG_116_02;
    BitField<2, 1, u8> WEEKEVENTREG_116_04;
    BitField<3, 1, u8> WEEKEVENTREG_116_08;
    BitField<4, 1, u8> WEEKEVENTREG_116_10;
    BitField<5, 1, u8> WEEKEVENTREG_116_20;
    BitField<6, 1, u8> WEEKEVENTREG_116_40;
    BitField<7, 1, u8> WEEKEVENTREG_116_80;
  };

  union WeekEventReg117 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_117_01;
    BitField<1, 1, u8> WEEKEVENTREG_117_02;
    BitField<2, 1, u8> WEEKEVENTREG_117_04;
    BitField<3, 1, u8> WEEKEVENTREG_117_08;
    BitField<4, 1, u8> WEEKEVENTREG_117_10;
    BitField<5, 1, u8> WEEKEVENTREG_117_20;
    BitField<6, 1, u8> WEEKEVENTREG_117_40;
    BitField<7, 1, u8> WEEKEVENTREG_117_80;
  };

  union WeekEventReg118 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_118_01;
    BitField<1, 1, u8> WEEKEVENTREG_118_02;
    BitField<2, 1, u8> WEEKEVENTREG_118_04;
    BitField<3, 1, u8> WEEKEVENTREG_118_08;
    BitField<4, 1, u8> WEEKEVENTREG_118_10;
    BitField<5, 1, u8> WEEKEVENTREG_118_20;
    BitField<6, 1, u8> WEEKEVENTREG_118_40;
    BitField<7, 1, u8> WEEKEVENTREG_118_80;
  };

  union WeekEventReg119 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_119_01;
    BitField<1, 1, u8> WEEKEVENTREG_119_02;
    BitField<2, 1, u8> WEEKEVENTREG_119_04;
    BitField<3, 1, u8> WEEKEVENTREG_119_08;
    BitField<4, 1, u8> WEEKEVENTREG_119_10;
    BitField<5, 1, u8> WEEKEVENTREG_119_20;
    BitField<6, 1, u8> WEEKEVENTREG_119_40;
    BitField<7, 1, u8> WEEKEVENTREG_119_80;
  };

  union WeekEventReg120 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_120_01;
    BitField<1, 1, u8> WEEKEVENTREG_120_02;
    BitField<2, 1, u8> WEEKEVENTREG_120_04;
    BitField<3, 1, u8> WEEKEVENTREG_120_08;
    BitField<4, 1, u8> WEEKEVENTREG_120_10;
    BitField<5, 1, u8> WEEKEVENTREG_120_20;
    BitField<6, 1, u8> WEEKEVENTREG_120_40;
    BitField<7, 1, u8> WEEKEVENTREG_120_80;
  };

  union WeekEventReg121 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_121_01;
    BitField<1, 1, u8> WEEKEVENTREG_121_02;
    BitField<2, 1, u8> WEEKEVENTREG_121_04;
    BitField<3, 1, u8> WEEKEVENTREG_121_08;
    BitField<4, 1, u8> WEEKEVENTREG_121_10;
    BitField<5, 1, u8> WEEKEVENTREG_121_20;
    BitField<6, 1, u8> WEEKEVENTREG_121_40;
    BitField<7, 1, u8> WEEKEVENTREG_121_80;
  };

  union WeekEventReg122 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_122_01;
    BitField<1, 1, u8> WEEKEVENTREG_122_02;
    BitField<2, 1, u8> WEEKEVENTREG_122_04;
    BitField<3, 1, u8> WEEKEVENTREG_122_08;
    BitField<4, 1, u8> WEEKEVENTREG_122_10;
    BitField<5, 1, u8> WEEKEVENTREG_122_20;
    BitField<6, 1, u8> WEEKEVENTREG_122_40;
    BitField<7, 1, u8> WEEKEVENTREG_122_80;
  };

  union WeekEventReg123 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_123_01;
    BitField<1, 1, u8> WEEKEVENTREG_123_02;
    BitField<2, 1, u8> WEEKEVENTREG_123_04;
    BitField<3, 1, u8> WEEKEVENTREG_123_08;
    BitField<4, 1, u8> WEEKEVENTREG_123_10;
    BitField<5, 1, u8> WEEKEVENTREG_123_20;
    BitField<6, 1, u8> WEEKEVENTREG_123_40;
    BitField<7, 1, u8> WEEKEVENTREG_123_80;
  };

  union WeekEventReg124 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_124_01;
    BitField<1, 1, u8> WEEKEVENTREG_124_02;
    BitField<2, 1, u8> WEEKEVENTREG_124_04;
    BitField<3, 1, u8> WEEKEVENTREG_124_08;
    BitField<4, 1, u8> WEEKEVENTREG_124_10;
    BitField<5, 1, u8> WEEKEVENTREG_124_20;
    BitField<6, 1, u8> WEEKEVENTREG_124_40;
    BitField<7, 1, u8> WEEKEVENTREG_124_80;
  };

  union WeekEventReg125 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_125_01;
    BitField<1, 1, u8> WEEKEVENTREG_125_02;
    BitField<2, 1, u8> WEEKEVENTREG_125_04;
    BitField<3, 1, u8> WEEKEVENTREG_125_08;
    BitField<4, 1, u8> WEEKEVENTREG_125_10;
    BitField<5, 1, u8> WEEKEVENTREG_125_20;
    BitField<6, 1, u8> WEEKEVENTREG_125_40;
    BitField<7, 1, u8> WEEKEVENTREG_125_80;
  };

  union WeekEventReg126 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_126_01;
    BitField<1, 1, u8> WEEKEVENTREG_126_02;
    BitField<2, 1, u8> WEEKEVENTREG_126_04;
    BitField<3, 1, u8> WEEKEVENTREG_126_08;
    BitField<4, 1, u8> WEEKEVENTREG_126_10;
    BitField<5, 1, u8> WEEKEVENTREG_126_20;
    BitField<6, 1, u8> WEEKEVENTREG_126_40;
    BitField<7, 1, u8> WEEKEVENTREG_126_80;
  };

  union WeekEventReg127 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_127_01;
    BitField<1, 1, u8> WEEKEVENTREG_127_02;
    BitField<2, 1, u8> WEEKEVENTREG_127_04;
    BitField<3, 1, u8> WEEKEVENTREG_127_08;
    BitField<4, 1, u8> WEEKEVENTREG_127_10;
    BitField<5, 1, u8> WEEKEVENTREG_127_20;
    BitField<6, 1, u8> WEEKEVENTREG_127_40;
    BitField<7, 1, u8> WEEKEVENTREG_127_80;
  };

  union WeekEventReg128 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_128_01;
    BitField<1, 1, u8> WEEKEVENTREG_128_02;
    BitField<2, 1, u8> WEEKEVENTREG_128_04;
    BitField<3, 1, u8> WEEKEVENTREG_128_08;
    BitField<4, 1, u8> WEEKEVENTREG_128_10;
    BitField<5, 1, u8> WEEKEVENTREG_128_20;
    BitField<6, 1, u8> WEEKEVENTREG_128_40;
    BitField<7, 1, u8> WEEKEVENTREG_128_80;
  };

  union WeekEventReg129 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_129_01;
    BitField<1, 1, u8> WEEKEVENTREG_129_02;
    BitField<2, 1, u8> WEEKEVENTREG_129_04;
    BitField<3, 1, u8> WEEKEVENTREG_129_08;
    BitField<4, 1, u8> WEEKEVENTREG_129_10;
    BitField<5, 1, u8> WEEKEVENTREG_129_20;
    BitField<6, 1, u8> WEEKEVENTREG_129_40;
    BitField<7, 1, u8> WEEKEVENTREG_129_80;
  };

  union WeekEventReg130 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_130_01;
    BitField<1, 1, u8> WEEKEVENTREG_130_02;
    BitField<2, 1, u8> WEEKEVENTREG_130_04;
    BitField<3, 1, u8> WEEKEVENTREG_130_08;
    BitField<4, 1, u8> WEEKEVENTREG_130_10;
    BitField<5, 1, u8> WEEKEVENTREG_130_20;
    BitField<6, 1, u8> WEEKEVENTREG_130_40;
    BitField<7, 1, u8> WEEKEVENTREG_130_80;
  };

  union WeekEventReg131 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_OWL_STATUE_CUTSCENE;
    BitField<1, 1, u8> WEEKEVENTREG_131_02;
    BitField<2, 1, u8> WEEKEVENTREG_131_04;
    BitField<3, 1, u8> WEEKEVENTREG_SKIP_MAP_TUTORIAL_BY_TINGLE;
    BitField<4, 1, u8> WEEKEVENTREG_DEKU_THRONE_ROOM_CAMERA_PAN;
    BitField<5, 1, u8> WEEKEVENTREG_TATL_MOON_TEAR_DIALOGUE;
    BitField<6, 1, u8> WEEKEVENTREG_131_40;
    BitField<7, 1, u8> WEEKEVENTREG_131_80;
  };

  union WeekEventReg132 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_132_01;
    BitField<1, 1, u8> WEEKEVENTREG_132_02;
    BitField<2, 1, u8> WEEKEVENTREG_132_04;
    BitField<3, 1, u8> WEEKEVENTREG_132_08;
    BitField<4, 1, u8> WEEKEVENTREG_MYSTERY_MILK_TALKED_TO_GORMAN_BROS;
    BitField<5, 1, u8> WEEKEVENTREG_132_20;
    BitField<6, 1, u8> WEEKEVENTREG_132_40;
    BitField<7, 1, u8> WEEKEVENTREG_132_80;
  };

  union WeekEventReg133 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_133_01;
    BitField<1, 1, u8> WEEKEVENTREG_133_02;
    BitField<2, 1, u8> WEEKEVENTREG_133_04;
    BitField<3, 1, u8> WEEKEVENTREG_133_08;
    BitField<4, 1, u8> WEEKEVENTREG_133_10;
    BitField<5, 1, u8> WEEKEVENTREG_133_20;
    BitField<6, 1, u8> WEEKEVENTREG_133_40;
    BitField<7, 1, u8> WEEKEVENTREG_133_80;
  };

  union WeekEventReg134 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_134_01;
    BitField<1, 1, u8> WEEKEVENTREG_134_02;
    BitField<2, 1, u8> WEEKEVENTREG_134_04;
    BitField<3, 1, u8> WEEKEVENTREG_134_08;
    BitField<4, 1, u8> WEEKEVENTREG_134_10;
    BitField<5, 1, u8> WEEKEVENTREG_134_20;
    BitField<6, 1, u8> WEEKEVENTREG_134_40;
    BitField<7, 1, u8> WEEKEVENTREG_134_80;
  };

  union WeekEventReg135 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_135_01;
    BitField<1, 1, u8> WEEKEVENTREG_135_02;
    BitField<2, 1, u8> WEEKEVENTREG_135_04;
    BitField<3, 1, u8> WEEKEVENTREG_135_08;
    BitField<4, 1, u8> WEEKEVENTREG_135_10;
    BitField<5, 1, u8> WEEKEVENTREG_135_20;
    BitField<6, 1, u8> WEEKEVENTREG_135_40;
    BitField<7, 1, u8> WEEKEVENTREG_135_80;
  };

  union WeekEventReg136 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_136_01;
    BitField<1, 1, u8> WEEKEVENTREG_136_02;
    BitField<2, 1, u8> WEEKEVENTREG_136_04;
    BitField<3, 1, u8> WEEKEVENTREG_CAMERA_PAN_WOODFALL_ENTER;
    BitField<4, 1, u8> WEEKEVENTREG_136_10;
    BitField<5, 1, u8> WEEKEVENTREG_136_20;
    BitField<6, 1, u8> WEEKEVENTREG_136_40;
    BitField<7, 1, u8> WEEKEVENTREG_136_80;
  };

  union WeekEventReg137 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_137_01;
    BitField<1, 1, u8> WEEKEVENTREG_137_02;
    BitField<2, 1, u8> WEEKEVENTREG_137_04;
    BitField<3, 1, u8> WEEKEVENTREG_SONG_OF_SOARING_PLAYED;
    BitField<4, 1, u8> WEEKEVENTREG_WOODFALL_TEMPLE_OPENED;
    BitField<5, 1, u8> WEEKEVENTREG_SNOWHEAD_TEMPLE_OPENED;
    BitField<6, 1, u8> WEEKEVENTREG_GREAT_BAY_TEMPLE_OPENED;
    BitField<7, 1, u8> WEEKEVENTREG_DEKU_FLOWN_IN;
  };

  union WeekEventReg138 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_138_01;
    BitField<1, 1, u8> WEEKEVENTREG_138_02;
    BitField<2, 1, u8> WEEKEVENTREG_138_04;
    BitField<3, 1, u8> WEEKEVENTREG_138_08;
    BitField<4, 1, u8> WEEKEVENTREG_138_10;
    BitField<5, 1, u8> WEEKEVENTREG_138_20;
    BitField<6, 1, u8> WEEKEVENTREG_138_40;
    BitField<7, 1, u8> WEEKEVENTREG_138_80;
  };

  union WeekEventReg139 {
    u8 raw;
    BitField<0, 1, u8> WEEKEVENTREG_139_01;
    BitField<1, 1, u8> WEEKEVENTREG_139_02;
    BitField<2, 1, u8> WEEKEVENTREG_139_04;
    BitField<3, 1, u8> WEEKEVENTREG_139_08;
    BitField<4, 1, u8> WEEKEVENTREG_139_10;
    BitField<5, 1, u8> WEEKEVENTREG_139_20;
    BitField<6, 1, u8> WEEKEVENTREG_139_40;
    BitField<7, 1, u8> WEEKEVENTREG_139_80;
  };
}  // namespace game
