#ifndef DDCBCAPI_h_INCLUDED
#define DDCBCAPI_h_INCLUDED

#include <glib.h>
#include <gmodule.h>

#include "ddcutil_c_api.h"
#include "ddcutil_status_codes.h"

#define BRIGHTNESS_CODE 0x10

/**
 *  DDCBC_Status adds a couple of possible errors in the -4000 range.
 */
typedef DDCA_Status DDCBC_Status;
#define DDCBC_BAD_VALUE -4000

/**
 *  ddcbc_display encompasses info of a supported ddcbc display.
 */
typedef struct ddcbc_display
{
  guint16 max_val;
  guint16 last_val; // last recorded value set after get call.
  DDCA_Display_Info info;
  DDCA_Display_Handle dh;
} ddcbc_display;

/**
 * ddcbc_display_list is a GArray of ddcbc_displays
 */
typedef struct
{
  guint ct;
  GArray *list;
} ddcbc_display_list;

/**
 *  ddcbc_display_get_brightness get the brightness of `disp` and caches the
 *  maximum possible brightness value. Any errors will be a DDC error.
 */
DDCBC_Status ddcbc_display_get_brightness (ddcbc_display *disp);

/**
 * ddcbc_bundle_set_brightness sets the brightness of a given monitor.
 */
DDCBC_Status ddcbc_display_set_brightness (ddcbc_display *disp,
                                           guint16 new_val);

ddcbc_display *ddcbc_display_list_get (ddcbc_display_list *dlist, guint index);

/**
 * ddcbc_display_list_init returns a list of supported ddcbc displays.
 * If wait is true, the function will instruct ddca to wait if a display
 * is locked by another process.
 */
ddcbc_display_list ddcbc_display_list_init (gboolean wait);

/**
 *  ddcbc_display_list_free frees the display list and closes all displays.
 */
void ddcbc_display_list_free (ddcbc_display_list *dlist);

#endif // DDCBCAPI_h_INCLUDED
