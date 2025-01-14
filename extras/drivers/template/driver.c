/**
 * @file driver.c
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief A template for HeliOS device drivers
 * @version 0.3.5
 * @date 2022-09-02
 *
 * @copyright
 * HeliOS Embedded Operating System
 * Copyright (C) 2020-2023 Manny Peterson <mannymsp@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "driver.h"



Base_t TO_FUNCTION(DEVICE_NAME, _self_register)(void) {

  /* DO NOT MODIFY THIS FUNCTION */

  return __RegisterDevice__(DEVICE_UID, (Char_t *)TO_LITERAL(DEVICE_NAME), DEVICE_STATE, DEVICE_MODE, TO_FUNCTION(DEVICE_NAME, _init),
                            TO_FUNCTION(DEVICE_NAME, _config), TO_FUNCTION(DEVICE_NAME, _read), TO_FUNCTION(DEVICE_NAME, _write),
                            TO_FUNCTION(DEVICE_NAME, _simple_read), TO_FUNCTION(DEVICE_NAME, _simple_write));
}



Base_t TO_FUNCTION(DEVICE_NAME, _init)(Device_t *device_) {
  Base_t ret = RETURN_FAILURE;

  /* INSERT CODE TO INITIALIZE DEVICE HERE */

  return ret;
}



Base_t TO_FUNCTION(DEVICE_NAME, _config)(Device_t *device_, Size_t *size_, Addr_t *config_) {
  Base_t ret = RETURN_FAILURE;

  /* INSERT CODE TO CONFIGURE DEVICE HERE */

  return ret;
}



Base_t TO_FUNCTION(DEVICE_NAME, _read)(Device_t *device_, Size_t *size_, Addr_t *data_) {
  Base_t ret = RETURN_FAILURE;

  /* INSERT CODE TO READ FROM DEVICE HERE */

  return ret;
}



Base_t TO_FUNCTION(DEVICE_NAME, _write)(Device_t *device_, Size_t *size_, Addr_t *data_) {
  Base_t ret = RETURN_FAILURE;

  /* INSERT CODE TO WRITE TO DEVICE HERE */

  return ret;
}



Base_t TO_FUNCTION(DEVICE_NAME, _simple_read)(Device_t *device_, Word_t *data_) {
  Base_t ret = RETURN_FAILURE;

  /* INSERT CODE TO READ FROM DEVICE HERE */

  return ret;
}



Base_t TO_FUNCTION(DEVICE_NAME, _simple_write)(Device_t *device_, Word_t *data_) {
  Base_t ret = RETURN_FAILURE;

  /* INSERT CODE TO WRITE TO DEVICE HERE */

  return ret;
}