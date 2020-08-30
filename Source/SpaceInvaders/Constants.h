#pragma once

/** Some "magic numbers" that are shared in many places of the code.
May make it an UT struct in the future, to customize values in the editor.
*/

/** How much you can go left/rigth of the origin.
The camera is positioned as to allow this much space of movement.
It should be possible to understand the limit of the frame with some math related
to the camera position, rotation and FOV, but that is overkill.*/
const float BattlefieldHalfWidth = 800;

/** This is close to where the startfields originates.*/
const float BattlefieldFarlimit = -2500;

/** This is behind the player spaceship, out of the field of view.*/
const float BattlefieldNearlimit = 400;