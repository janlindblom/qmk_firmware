/*
Copyright © 2022 Jan Lindblom (@janlindblom)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
/* We are going to present as a Reviung41 to fool Via/Vial */
#undef VENDOR_ID
#define VENDOR_ID 0x7807
#undef PRODUCT_ID
#define PRODUCT_ID 0xDCCB
