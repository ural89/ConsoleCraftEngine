#pragma once

// Show live Box2D body/joint counts on the HUD; useful for confirming
// Teardown()/Instantiate() cycles do not leak across R/N.
const bool DEBUG_COUNTS = false;

// ---- Simulation ----
const float FIXED_DT = 1.0f / 60.0f;
const float MAX_FRAME_TIME = 0.1f;
const int MAX_STEPS_PER_FRAME = 4;

// ---- Build rules ----
const float NODE_SNAP_RADIUS = 1.6f;
const float MAX_BEAM_LENGTH = 14.0f;
const float COST_PER_UNIT = 12.0f;
const float MIN_BEAM_LENGTH = 0.75f;
const float BEAM_DELETE_RADIUS = 3.0f;

// ---- Beam / node physics ----
const float BEAM_THICKNESS = 0.6f;
const float BEAM_DENSITY = 3.0f;
const float BEAM_FRICTION = 0.6f;
const float NODE_SIZE = 0.8f;
const short BRIDGE_GROUP = -1;  // beams/nodes never collide with each other
const short DECK_GROUP = -2;    // deck planks never collide with each other
const short VEHICLE_GROUP = -3; // chassis/wheels never collide with each other

// ---- Drawing ----
// Every shape is an engine Polygon, which draws its own outline through a
// LineDrawer pool sized once at construction; a shape whose perimeter (in
// console cells) exceeds its budget loses its last edges. See
// PolygonFactory::CreateBox for how these are passed in.
const int TERRAIN_GLYPHS = 120; // a full-height cliff box is ~75 cells around
const int DECK_GLYPHS = 16;
const int BEAM_GLYPHS = 40;
const int NODE_GLYPHS = 8;
const int CHASSIS_GLYPHS = 20;
const int WHEEL_GLYPHS = 12;
const int PREVIEW_GLYPHS = 40;

const int TERRAIN_COLOR = 8;
const int DECK_COLOR = 7;
const int NODE_COLOR = 4;
const int VEHICLE_COLOR = 6;
const int BEAM_OK_COLOR = 2;       // green: comfortably within its limit
const int BEAM_WARN_COLOR = 3;     // yellow: past STRESS_WARN
const int BEAM_CRITICAL_COLOR = 1; // red: past STRESS_CRITICAL, or snapped
const int PREVIEW_COLOR = 3;

// ---- Breaking ----
const float BEAM_BREAK_FORCE = 3200.0f;
const float STRESS_EMA_RATE = 6.0f; // higher = reacts faster to load spikes
const float STRESS_WARN = 0.5f;
const float STRESS_CRITICAL = 0.85f;

// ---- Deck ----
const float DECK_THICKNESS = 0.5f;
const float DECK_DENSITY = 1.2f;

// ---- Vehicle ----
const float VEHICLE_CHASSIS_HALF_W = 1.6f;
const float VEHICLE_CHASSIS_HALF_H = 0.55f;
const float VEHICLE_WHEEL_RADIUS = 0.85f;
const float VEHICLE_DENSITY = 1.4f;
const float VEHICLE_MAX_MOTOR_TORQUE = 40.0f;
const float VEHICLE_MOTOR_SPEED = 11.0f;
const float FAIL_Y_MARGIN = 6.0f;  // world Y past groundY that counts as "fell off"
const float TEST_TIMEOUT = 25.0f;

// ---- Cursor ----
const float CURSOR_STEP_X = 2.0f;
const float CURSOR_STEP_Y = 1.0f;

enum class BridgePhase
{
    Build,
    Test,
    Won,
    Lost
};
