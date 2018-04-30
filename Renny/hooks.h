#pragma once

bool Hook(void * toHook, void * ourFunct, int len);

void onAutoAttack();

void onSpellCast();

void onCast();

void onWallClick();

void applyHooks();