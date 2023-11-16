/* Newlib C includes */
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define JSMN_HEADER

/* app includes */
#include "jsmn.h"
#include "parse_stop_json.h"
#include "stop.h"

/** The number of keys + values in for each object type in our JSON string */
#define DEPARTURE_TOK_COUNT 18
#define HEADWAY_TOK_COUNT 14
#define ROUTE_DIRECTION_TOK_COUNT \
  (12 + (MAX_DEPARTURES * (DEPARTURE_TOK_COUNT + HEADWAY_TOK_COUNT)))
#define STOP_TOK_COUNT (6 + (MAX_ROUTES * ROUTE_DIRECTION_TOK_COUNT))

/** With jsmn JSON objects count as a token, so we need to offset by an
 *  additional 1 for each level deeper we go.
 *  These offsets need to be temporary though, because objects don't have a
 *  value to account for. At least that's what I believe the reason to be...
 */
// #define STOP_TOK tokens[t + 1]
#define ROUTE_DIRECTION_TOK tokens[t + rdir + 2]
#define DEPARTURE_TOK tokens[t + rdir + dep + 3]

/** Compares a string with a jsmn token value. */
static bool jsoneq(const char *json_ptr, jsmntok_t *tok, const char *string) {
  if (tok->type == JSMN_STRING &&
      (int)strlen(string) == tok->end - tok->start &&
      strncmp(json_ptr + tok->start, string, tok->end - tok->start) == 0) {
    return true;
  }
  return false;
}

static bool unique_disply_text(
    const char *json_ptr, RouteDirection *route_direction, jsmntok_t *tok,
    const size_t valid_departure_count
) {
  for (int i = 0; i < valid_departure_count; i++) {
    Departure *departure = &route_direction->departures[i];
    if (jsoneq(json_ptr, tok, departure->display_text)) {
      return false;
    }
  }
  return true;
}

/** Iterates through the Departures array objects to find desired values. */
static void parse_departures(
    char *json_ptr, unsigned int t, jsmntok_t tokens[], int rdir,
    const size_t departures_count, RouteDirection *route_direction,
    long time_now
) {
  size_t valid_departure_count = 0;

  for (int dep_num = 0; dep_num < departures_count; dep_num++) {
    Departure *departure = &route_direction->departures[valid_departure_count];
    bool departure_uniq = false;
    bool edt_in_future = false;

    /** Increase t by 1 to step into the object */
    t++;

    /** The number of keys in the Departure object.
     *
     *  ROUTE_DIRECTION_TOK is a Departure object,
     *  so ROUTE_DIRECTION_TOK.size is the number of Departure keys.
     */
    const size_t departure_size = ROUTE_DIRECTION_TOK.size;
    // printf("***********Start Departure (t: %d, dep_num: %d, departure_size:
    // %d)**********", t,
    //         dep_num, departure_size);
    for (int dep = 0; dep < (departure_size * 2); dep++) {
      if (jsoneq(json_ptr, &DEPARTURE_TOK, "DisplayText")) {
        dep++;
#ifdef CONFIG_DEBUG
        printf("* DisplayText:");
        print_token_substring(json_ptr, &DEPARTURE_TOK);
#endif
        departure_uniq = unique_disply_text(
            json_ptr, route_direction, &DEPARTURE_TOK, valid_departure_count
        );

        if (departure_uniq) {
          strncpy(
              departure->display_text, json_ptr + DEPARTURE_TOK.start,
              DEPARTURE_TOK.end - DEPARTURE_TOK.start
          );
          departure->display_text[(DEPARTURE_TOK.end - DEPARTURE_TOK.start)] =
              '\0';
          if (edt_in_future) {
            goto check_validity;
          }
        } else {
          break;
        }
      } else if (jsoneq(json_ptr, &DEPARTURE_TOK, "EDT")) {
        dep++;
        /* EDT ex: /Date(1648627309163-0400)\, where 1648627309163 is ms since
         * the epoch. We increase the pointer by 6 to remove the leading
         * '/Date(' for atoi(). This also ignores the timezone which we don't
         * need.
         */
        char *edt_string = json_ptr + DEPARTURE_TOK.start + 7;
        // edt_string[10] = '\0';
        long edt = atol(edt_string);
        printf("* EDT: %ld", edt);
        if (edt > time_now) {
          departure->etd = edt;
          edt_in_future = true;
          if (departure_uniq) {
            goto check_validity;
          }
        } else if (departure_uniq) {
          departure->display_text[0] = '\0';
          break;
        } else {
          break;
        }
      } else if (jsoneq(json_ptr, &DEPARTURE_TOK, "ETA")) {
        dep++;
      } else if (jsoneq(json_ptr, &DEPARTURE_TOK, "GoogleTripId")) {
        dep++;
      } else if (jsoneq(json_ptr, &DEPARTURE_TOK, "LastUpdated")) {
        dep++;
      } else if (jsoneq(json_ptr, &DEPARTURE_TOK, "SDT")) {
        dep++;
      } else if (jsoneq(json_ptr, &DEPARTURE_TOK, "STA")) {
        dep++;
      } else if (jsoneq(json_ptr, &DEPARTURE_TOK, "VehicleId")) {
        dep++;
      } else {
        dep++;
        printf(
            "Unexpected key in Departures: %.*s\n",
            DEPARTURE_TOK.end - DEPARTURE_TOK.start,
            json_ptr + DEPARTURE_TOK.start
        );
      }

    check_validity:
      if (departure_uniq && edt_in_future) {
        valid_departure_count++;
        break;
      }
    }
    t += (departure_size * 2);
    // printf("*********************(t: %d)********************\n", t);
  }
#ifdef CONFIG_DEBUG
  for (int i = 0; i < MAX_DEPARTURES; i++) {
    printf(
        "Uniq display text(s) %d: %s", i,
        route_direction->departures[i].display_text
    );
  }
#endif
  route_direction->departures_size = valid_departure_count;
}

/** Iterates through the RouteDirections array objects to find desired values.
 */
static void parse_route_directions(
    char *json_ptr, unsigned int t, jsmntok_t tokens[],
    const size_t route_directions_count, Stop *stop, long time_now
) {
  size_t valid_route_count = 0;

  for (int rd_num = 0; rd_num < route_directions_count; rd_num++) {
    RouteDirection *route_direction =
        &stop->route_directions[valid_route_count];
    /** The number of keys in the RouteDirection object.
     *
     *  tokens[t + 1] is a RouteDirection object,
     *  so tokens[t + 1].size is the number of RouteDirection keys.
     */
    const size_t route_direction_size = tokens[t + 1].size;
    // printf("=======Start Route Direction (t: %d, Route_Direction_Size: %d,
    // rd_num: %d)======", t,
    //         route_direction_size * 2, rd_num);
    /* jsmntok::size is the number of keys but we're iterating over keys and
     * values, so we need to double the size to get the true count.
     */
    for (int rdir = 0; rdir < (route_direction_size * 2); rdir++) {
      if (jsoneq(json_ptr, &ROUTE_DIRECTION_TOK, "Direction")) {
        rdir++;
        route_direction->direction_code =
            *(json_ptr + ROUTE_DIRECTION_TOK.start);
        printf("- Direction: %c", *(json_ptr + ROUTE_DIRECTION_TOK.start));
      } else if (jsoneq(json_ptr, &ROUTE_DIRECTION_TOK, "IsDone")) {
        rdir++;
      } else if (jsoneq(json_ptr, &ROUTE_DIRECTION_TOK, "IsHeadway")) {
        rdir++;
      } else if (jsoneq(json_ptr, &ROUTE_DIRECTION_TOK, "RouteId")) {
        rdir++;
        route_direction->id = atoi(json_ptr + ROUTE_DIRECTION_TOK.start);
        printf("- RouteId: %d", atoi(json_ptr + ROUTE_DIRECTION_TOK.start));
      } else if (jsoneq(json_ptr, &ROUTE_DIRECTION_TOK, "Departures")) {
        rdir++;
        if ((ROUTE_DIRECTION_TOK.type == JSMN_ARRAY) &&
            (ROUTE_DIRECTION_TOK.size > 0)) {
          parse_departures(
              json_ptr, t, tokens, rdir, ROUTE_DIRECTION_TOK.size,
              route_direction, time_now
          );
          valid_route_count++;
        } else {
          break;
        }
      } else if (jsoneq(json_ptr, &ROUTE_DIRECTION_TOK, "HeadwayDepartures")) {
        rdir++;
        if ((ROUTE_DIRECTION_TOK.type == JSMN_ARRAY) &&
            (ROUTE_DIRECTION_TOK.size > 0)) {
          /* We don't care about this array but we do need to account for it's
           * size */
          t += (ROUTE_DIRECTION_TOK.size * 2) + 1;
        }
      } else {
        /* We don't care about other keys so skip their values */
        rdir++;
        printf(
            "Unexpected key in RouteDirections: %.*s\n",
            ROUTE_DIRECTION_TOK.end - ROUTE_DIRECTION_TOK.start,
            json_ptr + ROUTE_DIRECTION_TOK.start
        );
      }
    }
    /* Increase t by an additional 1 to step into the next object */
    t += (route_direction_size * 2) + 1;
    // printf("==============================(t: %d, rd_num:
    // %d)========================\n", t,
    //         rd_num);
  }
  stop->routes_size = valid_route_count;
}

/** Parses a JSON string with jsmn, then iterates through the jsmn key tokens
 *  to find desired values.
 *
 * TODO: Acount for size of *optional* arrays while iterating.
 */
int parse_stop_json(char *json_ptr, Stop *stop) {
  static jsmn_parser p;

  /** The number of maximum possible tokens we expect in our JSON string + 1 for
   * the \0 delimiter. */
  static jsmntok_t tokens[STOP_TOK_COUNT + 1];

  /** The jsmn token counter. */
  static unsigned int t;

  jsmn_init(&p);
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);

  /** The number of tokens *allocated* from tokens array to parse the JSON
   * string */
  const int ret = jsmn_parse(
      &p, json_ptr, strlen(json_ptr), tokens, sizeof(tokens) / sizeof(jsmntok_t)
  );

  switch (ret) {
    case 0:
      printf("Parsed Empty JSON string.");
      return EXIT_FAILURE;
    case JSMN_ERROR_NOMEM:
      printf("Failed to parse JSON; Not enough tokens were provided.");
      return EXIT_FAILURE;
    case JSMN_ERROR_INVAL:
      printf("Failed to parse JSON; Invalid character inside JSON string.");
      return EXIT_FAILURE;
    case JSMN_ERROR_PART:
      printf(
          "Failed to parse JSON; The string is not a full JSON packet, more "
          "bytes expected."
      );
      return EXIT_FAILURE;
    default:
      break;
  }
  printf("Tokens allocated: %d/%d\n", ret, STOP_TOK_COUNT);

  /* Set the starting position for t */
  switch (tokens[0].type) {
    case JSMN_ARRAY:
      /* If the root token is an array, we assume the next token is an object;
       * t is set to 2 so we can start in the object.
       */
      t = 2;
      break;
    case JSMN_OBJECT:
      /* If the root token an object t is set to 1 so we can start in the
       * object. */
      t = 1;
      break;
    default:
      printf("Top level token isn't an array or object.");
      return EXIT_FAILURE;
  }

  long time_now = (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
  if (time_now < 0) {
    return 2;
  }

  /* We want to loop over all the keys of the root object.
   * We know the token after a key is a value so we skip that iteration.
   */
  while (t < ret) {
    if (jsoneq(json_ptr, &tokens[t], "LastUpdated")) {
      t++;
      char *last_updated_string = json_ptr + tokens[t].start + 7;
      // last_updated_string[10] = '\0';
      printf("LastUpdated: %lld\n", strtoll(last_updated_string, NULL, 10));
      unsigned long long new_last_updated =
          strtoll(last_updated_string, NULL, 10);
      if (stop->last_updated < new_last_updated) {
        stop->last_updated = new_last_updated;
      } else {
        printf("StopDepartures not updated, skipping.");
        break;
      }
    } else if (jsoneq(json_ptr, &tokens[t], "RouteDirections")) {
      /* Increase t by an additional 1 to step into the array */
      t++;
      /* tokens[t] is the RouteDirections array in this case,
       * so tokens[t].size is the number of RouteDirections
       */
      if (tokens[t].type == JSMN_ARRAY && tokens[t].size > 0) {
        parse_route_directions(
            json_ptr, t, tokens, tokens[t].size, stop, time_now
        );
      } else {
        printf("No RouteDirections to parse.");
        break;
      }
    } else if (jsoneq(json_ptr, &tokens[t], "StopId")) {
      t++;
      /** TODO: Maybe verify the ID matches the one requested? Seems silly. */
      printf("StopId: %d\n", atoi(json_ptr + tokens[t].start));
    } else {
      t++;
      printf(
          "Unexpected key in Stop: %.*s\n", tokens[t].end - tokens[t].start,
          json_ptr + tokens[t].start
      );
    }
    t++;
  }
  return EXIT_SUCCESS;
}
