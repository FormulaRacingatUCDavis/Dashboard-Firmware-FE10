-- ======================================================================
-- CAN_Full_P4_Example01.ctl generated from CAN_Full_P4_Example01
-- 06/07/2023 at 19:43
-- This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
-- ======================================================================

-- TopDesign
-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-044 kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:rx(0)\ : label is "PORT(7,0)";
attribute port_location of \UART:tx(0)\ : label is "PORT(7,1)";

-- === CAN ===
attribute port_location of RX(0) : label is "PORT(0,0)";
attribute port_location of TX(0) : label is "PORT(0,1)";
-- PSoC Clock Editor
-- Directives Editor
-- Analog Device Editor
