/*
 * @file screen.h
 * @brief Screen Controls
 */

#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// Init Screen
void screen_init();
// Set screen to free
void set_free(void);
// Set screen to busy
void set_busy(void);

#ifdef __cplusplus
extern }
#endif

#endif // SCREEN_H_INCLUDED