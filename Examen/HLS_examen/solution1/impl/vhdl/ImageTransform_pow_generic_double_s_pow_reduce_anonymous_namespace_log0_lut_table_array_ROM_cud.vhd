-- ==============================================================
-- Generated by Vitis HLS v2023.2
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity ImageTransform_pow_generic_double_s_pow_reduce_anonymous_namespace_log0_lut_table_array_ROM_cud is 
    generic(
             DataWidth     : integer := 109; 
             AddressWidth     : integer := 6; 
             AddressRange    : integer := 64
    ); 
    port (
 
          address0        : in std_logic_vector(AddressWidth-1 downto 0); 
          ce0             : in std_logic; 
          q0              : out std_logic_vector(DataWidth-1 downto 0);

          reset               : in std_logic;
          clk                 : in std_logic
    ); 
end entity; 


architecture rtl of ImageTransform_pow_generic_double_s_pow_reduce_anonymous_namespace_log0_lut_table_array_ROM_cud is 
 
signal address0_tmp : std_logic_vector(AddressWidth-1 downto 0); 

type mem_array is array (0 to AddressRange-1) of std_logic_vector (DataWidth-1 downto 0); 

signal mem0 : mem_array := (
    0 => "1111111101111100000111101111110100011001001011101110001101001111110011101110101001010001100111100010101010000", 1 => "1111111101111100000111101111110100011001001011101110001101001111110011101110101001010001100111100010101010000", 2 => "1111111101111100000111101111110100011001001011101110001101001111110011101110101001010001100111100010101010000", 3 => "0000011110011100110011011100001000001100110100010000010110000111110110101000100010001100100010001001011011001", 
    4 => "0000011110011100110011011100001000001100110100010000010110000111110110101000100010001100100010001001011011001", 5 => "0001000000000001101101111011001010110111011010001110100111011000011100101110011111101101100100110010110110111", 6 => "0001000000000001101101111011001010110111011010001110100111011000011100101110011111101101100100110010110110111", 7 => "0001100010101111011111010101101001110010011110000110101111111101111011000100100011110101100010101111011110101", 
    8 => "0001100010101111011111010101101001110010011110000110101111111101111011000100100011110101100010101111011110101", 9 => "0001100010101111011111010101101001110010011110000110101111111101111011000100100011110101100010101111011110101", 10 => "0010000110101011001111000000000101101000111101111101101100001100001101100000000011010101100101110001000001000", 11 => "0010000110101011001111000000000101101000111101111101101100001100001101100000000011010101100101110001000001000", 
    12 => "0010101011111010100111111101001111000001101010100100011101000110110101000001000000101011100101110010111010010", 13 => "0010101011111010100111111101001111000001101010100100011101000110110101000001000000101011100101110010111010010", 14 => "0010101011111010100111111101001111000001101010100100011101000110110101000001000000101011100101110010111010010", 15 => "0011010010100011111110010111011000101110111000101010101000101110001001101011111101000000111010011011101010100", 
    16 => "0011010010100011111110010111011000101110111000101010101000101110001001101011111101000000111010011011101010100", 17 => "0011010010100011111110010111011000101110111000101010101000101110001001101011111101000000111010011011101010100", 18 => "0011111010101110010101111101011010000000100101011101011001001011000000010110110110001001011010100010111110010", 19 => "0011111010101110010101111101011010000000100101011101011001001011000000010110110110001001011010100010111110010", 
    20 => "0011111010101110010101111101011010000000100101011101011001001011000000010110110110001001011010100010111110010", 21 => "0011111010101110010101111101011010000000100101011101011001001011000000010110110110001001011010100010111110010", 22 => "0100100100100001101001110100000111101100100111010010110100110000101111101001100000101011011110010010110100110", 23 => "0100100100100001101001110100000111101100100111010010110100110000101111101001100000101011011110010010110100110", 
    24 => "0100100100100001101001110100000111101100100111010010110100110000101111101001100000101011011110010010110100110", 25 => "0100100100100001101001110100000111101100100111010010110100110000101111101001100000101011011110010010110100110", 26 => "0101010000000110110101110001100111111011101111100100001010001000000011111001110010110101010010101101111010111", 27 => "0101010000000110110101110001100111111011101111100100001010001000000011111001110010110101010010101101111010111", 
    28 => "0101010000000110110101110001100111111011101111100100001010001000000011111001110010110101010010101101111010111", 29 => "0101010000000110110101110001100111111011101111100100001010001000000011111001110010110101010010101101111010111", 30 => "0101111101101000000001111110110001111001100000110101001100000111011010101110000100100110011010010011110010101", 31 => "0101111101101000000001111110110001111001100000110101001100000111011010101110000100100110011010010011110010101", 
    32 => "1011001111011000100101000001000110010100101110100010000011011111000110111100010111100111100010100000101000011", 33 => "1011001111011000100101000001000110010100101110100010000011011111000110111100010111100111100010100000101000011", 34 => "1011100111011110101011000100111001101010100101101010101101000001010110111100101011111011110110100000111011111", 35 => "1011100111011110101011000100111001101010100101101010101101000001010110111100101011111011110110100000111011111", 
    36 => "1100000000001001111011100010001001011100101100101000111000110101001001000101110101111001001011110000000011100", 37 => "1100000000001001111011100010001001011100101100101000111000110101001001000101110101111001001011110000000011100", 38 => "1100000000001001111011100010001001011100101100101000111000110101001001000101110101111001001011110000000011100", 39 => "1100011001011100001011110110110111100011111110101001111111110111100000110011101000010011101110000010101100010", 
    40 => "1100011001011100001011110110110111100011111110101001111111110111100000110011101000010011101110000010101100010", 41 => "1100011001011100001011110110110111100011111110101001111111110111100000110011101000010011101110000010101100010", 42 => "1100110011010111011010011100001100110000100000010111101001100011010011001000100101100111001011001011100101011", 43 => "1100110011010111011010011100001100110000100000010111101001100011010011001000100101100111001011001011100101011", 
    44 => "1101001101111101101111100001101111001010000001110011101110111110111001110010011000111101100011111110100000111", 45 => "1101001101111101101111100001101111001010000001110011101110111110111001110010011000111101100011111110100000111", 46 => "1101001101111101101111100001101111001010000001110011101110111110111001110010011000111101100011111110100000111", 47 => "1101101001010001011110010000110011011001010001001001110010110111110000110011000101101111100110100011110010010", 
    48 => "1101101001010001011110010000110011011001010001001001110010110111110000110011000101101111100110100011110010010", 49 => "1101101001010001011110010000110011011001010001001001110010110111110000110011000101101111100110100011110010010", 50 => "1110000101010101000101111000111011101110001110111111110101100101111001000110001001010001101111000010101111101", 51 => "1110000101010101000101111000111011101110001110111111110101100101111001000110001001010001101111000010101111101", 
    52 => "1110000101010101000101111000111011101110001110111111110101100101111001000110001001010001101111000010101111101", 53 => "1110000101010101000101111000111011101110001110111111110101100101111001000110001001010001101111000010101111101", 54 => "1110100010001011010011000111001000110011110000111001011110110011111010100101000010010111101100010001000011010", 55 => "1110100010001011010011000111001000110011110000111001011110110011111010100101000010010111101100010001000011010", 
    56 => "1110100010001011010011000111001000110011110000111001011110110011111010100101000010010111101100010001000011010", 57 => "1110111111110111000001101001110100010000011111011001000000011111000100001000010110011000111001101011010011101", 58 => "1110111111110111000001101001110100010000011111011001000000011111000100001000010110011000111001101011010011101", 59 => "1110111111110111000001101001110100010000011111011001000000011111000100001000010110011000111001101011010011101", 
    60 => "1110111111110111000001101001110100010000011111011001000000011111000100001000010110011000111001101011010011101", 61 => "1111011110011011011110000011100101111011001000100010001100111100100100001010101101001100101011000011101101100", 62 => "1111011110011011011110000011100101111011001000100010001100111100100100001010101101001100101011000011101101100", 63 => "1111011110011011011110000011100101111011001000100010001100111100100100001010101101001100101011000011101101100");



begin 

 
memory_access_guard_0: process (address0) 
begin
      address0_tmp <= address0;
--synthesis translate_off
      if (CONV_INTEGER(address0) > AddressRange-1) then
           address0_tmp <= (others => '0');
      else 
           address0_tmp <= address0;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
 
        if (ce0 = '1') then  
            q0 <= mem0(CONV_INTEGER(address0_tmp)); 
        end if;

end if;
end process;

end rtl;

