// Hitachi HD44780A00 32 to 127
static uint8_t const __code font_A00[96][5] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },  // 20  32
	{ 0x00, 0x00, 0x4F, 0x00, 0x00 },  // 21  33  !
	{ 0x00, 0x07, 0x00, 0x07, 0x00 },  // 22  34  "
	{ 0x14, 0x7F, 0x14, 0x7F, 0x14 },  // 23  35  #
	{ 0x24, 0x2A, 0x7F, 0x2A, 0x12 },  // 24  36  $
	{ 0x23, 0x13, 0x08, 0x64, 0x62 },  // 25  37  %
	{ 0x36, 0x49, 0x55, 0x22, 0x50 },  // 26  38  &
	{ 0x00, 0x05, 0x03, 0x00, 0x00 },  // 27  39  '
	{ 0x00, 0x1C, 0x22, 0x41, 0x00 },  // 28  40  (
	{ 0x00, 0x41, 0x22, 0x1C, 0x00 },  // 29  41  )
	{ 0x14, 0x08, 0x3E, 0x08, 0x14 },  // 2A  42  *
	{ 0x08, 0x08, 0x3E, 0x08, 0x08 },  // 2B  43  +
	{ 0x00, 0x50, 0x30, 0x00, 0x00 },  // 2C  44  ,
	{ 0x08, 0x08, 0x08, 0x08, 0x08 },  // 2D  45  -
	{ 0x00, 0x60, 0x60, 0x00, 0x00 },  // 2E  46  .
	{ 0x20, 0x10, 0x08, 0x04, 0x02 },  // 2F  47  /
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E },  // 30  48  0
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 },  // 31  49  1
	{ 0x42, 0x61, 0x51, 0x49, 0x46 },  // 32  50  2
	{ 0x21, 0x41, 0x45, 0x4B, 0x31 },  // 33  51  3
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 },  // 34  52  4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 },  // 35  53  5
	{ 0x3C, 0x4A, 0x49, 0x49, 0x30 },  // 36  54  6
	{ 0x03, 0x01, 0x71, 0x09, 0x07 },  // 37  55  7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 },  // 38  56  8
	{ 0x06, 0x49, 0x49, 0x29, 0x1E },  // 39  57  9
	{ 0x00, 0x36, 0x36, 0x00, 0x00 },  // 3A  58  :
	{ 0x00, 0x56, 0x36, 0x00, 0x00 },  // 3B  59  ;
	{ 0x08, 0x14, 0x22, 0x41, 0x00 },  // 3C  60  <
	{ 0x14, 0x14, 0x14, 0x14, 0x14 },  // 3D  61  =
	{ 0x00, 0x41, 0x22, 0x14, 0x08 },  // 3E  62  >
	{ 0x02, 0x01, 0x51, 0x09, 0x06 },  // 3F  63  ?
	{ 0x32, 0x49, 0x79, 0x41, 0x3E },  // 40  64  @
	{ 0x7E, 0x11, 0x11, 0x11, 0x7E },  // 41  65  A
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 },  // 42  66  B
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 },  // 43  67  C
	{ 0x7F, 0x41, 0x41, 0x22, 0x1C },  // 44  68  D
	{ 0x7F, 0x49, 0x49, 0x49, 0x41 },  // 45  69  E
	{ 0x7F, 0x09, 0x09, 0x09, 0x01 },  // 46  70  F
	{ 0x3E, 0x41, 0x49, 0x49, 0x7A },  // 47  71  G
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F },  // 48  72  H
	{ 0x00, 0x41, 0x7F, 0x41, 0x00 },  // 49  73  I
	{ 0x20, 0x40, 0x41, 0x3F, 0x01 },  // 4A  74  J
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 },  // 4B  75  K
	{ 0x7F, 0x40, 0x40, 0x40, 0x40 },  // 4C  76  L
	{ 0x7F, 0x02, 0x0C, 0x02, 0x7F },  // 4D  77  M
	{ 0x7F, 0x04, 0x08, 0x10, 0x7F },  // 4E  78  N
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E },  // 4F  79  O
	{ 0x7F, 0x09, 0x09, 0x09, 0x06 },  // 50  80  P
	{ 0x3E, 0x41, 0x51, 0x21, 0x5E },  // 51  81  Q
	{ 0x7F, 0x09, 0x19, 0x29, 0x46 },  // 52  82  R
	{ 0x46, 0x49, 0x49, 0x49, 0x31 },  // 53  83  S
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 },  // 54  84  T
	{ 0x3F, 0x40, 0x40, 0x40, 0x3F },  // 55  85  U
	{ 0x1F, 0x20, 0x40, 0x20, 0x1F },  // 56  86  V
	{ 0x3F, 0x40, 0x38, 0x40, 0x3F },  // 57  87  W
	{ 0x63, 0x14, 0x08, 0x14, 0x63 },  // 58  88  X
	{ 0x07, 0x08, 0x70, 0x08, 0x07 },  // 59  89  Y
	{ 0x61, 0x51, 0x49, 0x45, 0x43 },  // 5A  90  Z
	{ 0x7F, 0x41, 0x41, 0x00, 0x00 },  // 5B  91  [
	{ 0x15, 0x16, 0x7C, 0x16, 0x15 },  // 5C  92  '\'
	{ 0x00, 0x41, 0x41, 0x7F, 0x00 },  // 5D  93  ]
	{ 0x04, 0x02, 0x01, 0x02, 0x04 },  // 5E  94  ^
	{ 0x40, 0x40, 0x40, 0x40, 0x40 },  // 5F  95  _
	{ 0x00, 0x01, 0x02, 0x04, 0x00 },  // 60  96  `
	{ 0x20, 0x54, 0x54, 0x54, 0x78 },  // 61  97  a
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 },  // 62  98  b
	{ 0x38, 0x44, 0x44, 0x44, 0x20 },  // 63  99  c
	{ 0x38, 0x44, 0x44, 0x48, 0x7F },  // 64 100  d
	{ 0x38, 0x54, 0x54, 0x54, 0x18 },  // 65 101  e
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 },  // 66 102  f
	{ 0x0C, 0x52, 0x52, 0x52, 0x3E },  // 67 103  g
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 },  // 68 104  h
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 },  // 69 105  i
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 },  // 6A 106  j
	{ 0x7F, 0x10, 0x28, 0x44, 0x00 },  // 6B 107  k
	{ 0x00, 0x41, 0x7F, 0x40, 0x00 },  // 6C 108  l
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 },  // 6D 109  m
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 },  // 6E 110  n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 },  // 6F 111  o
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 },  // 70 112  p
	{ 0x08, 0x14, 0x14, 0x18, 0x7C },  // 71 113  q
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 },  // 72 114  r
	{ 0x48, 0x54, 0x54, 0x54, 0x20 },  // 73 115  s
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 },  // 74 116  t
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C },  // 75 117  u
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C },  // 76 118  v
	{ 0x3C, 0x40, 0x38, 0x40, 0x3C },  // 77 119  w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 },  // 78 120  x
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C },  // 79 121  y
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 },  // 7A 122  z
	{ 0x00, 0x08, 0x36, 0x41, 0x00 },  // 7B 123  {
	{ 0x00, 0x00, 0x7F, 0x00, 0x00 },  // 7C 124  |
	{ 0x00, 0x41, 0x36, 0x08, 0x00 },  // 7D 125  }
	{ 0x08, 0x08, 0x2A, 0x1C, 0x08 },  // 7E 126  ~
	{ 0x08, 0x1C, 0x2A, 0x08, 0x08 }   // 7F 127
};

// Hitachi HD44780A00 160 to 255
static uint8_t const __code font_A00h[96][5] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },  // A0 160
	{ 0x70, 0x50, 0x70, 0x00, 0x00 },  // A1 161
	{ 0x00, 0x00, 0x0F, 0x01, 0x01 },  // A2 162
	{ 0x40, 0x40, 0x78, 0x00, 0x00 },  // A3 163
	{ 0x10, 0x20, 0x40, 0x00, 0x00 },  // A4 164
	{ 0x00, 0x18, 0x18, 0x00, 0x00 },  // A5 165
	{ 0x0A, 0x0A, 0x4A, 0x2A, 0x1E },  // A6 166
	{ 0x04, 0x44, 0x34, 0x14, 0x0C },  // A7 167
	{ 0x20, 0x10, 0x78, 0x04, 0x00 },  // A8 168
	{ 0x18, 0x08, 0x4C, 0x48, 0x38 },  // A9 169
	{ 0x44, 0x44, 0x7C, 0x44, 0x44 },  // AA 170
	{ 0x48, 0x28, 0x18, 0x7C, 0x08 },  // AB 171
	{ 0x08, 0x7C, 0x08, 0x28, 0x18 },  // AC 172
	{ 0x40, 0x48, 0x48, 0x78, 0x40 },  // AD 173
	{ 0x54, 0x54, 0x54, 0x7C, 0x00 },  // AE 174
	{ 0x18, 0x00, 0x58, 0x40, 0x38 },  // AF 175
	{ 0x08, 0x08, 0x08, 0x08, 0x08 },  // B0 176
	{ 0x01, 0x41, 0x3D, 0x09, 0x07 },  // B1 177
	{ 0x10, 0x08, 0x7C, 0x02, 0x01 },  // B2 178
	{ 0x0E, 0x02, 0x43, 0x22, 0x1E },  // B3 179
	{ 0x42, 0x42, 0x7E, 0x42, 0x42 },  // B4 180
	{ 0x22, 0x12, 0x0A, 0x7F, 0x02 },  // B5 181
	{ 0x42, 0x3F, 0x02, 0x42, 0x3E },  // B6 182
	{ 0x0A, 0x0A, 0x7F, 0x0A, 0x0A },  // B7 183
	{ 0x08, 0x46, 0x42, 0x22, 0x1E },  // B8 184
	{ 0x04, 0x03, 0x42, 0x3E, 0x02 },  // B9 185
	{ 0x42, 0x42, 0x42, 0x42, 0x7E },  // BA 186
	{ 0x02, 0x4F, 0x22, 0x1F, 0x02 },  // BB 187
	{ 0x4A, 0x4A, 0x40, 0x20, 0x1C },  // BC 188
	{ 0x42, 0x22, 0x12, 0x2A, 0x46 },  // BD 189
	{ 0x02, 0x3F, 0x42, 0x4A, 0x46 },  // BE 190
	{ 0x06, 0x48, 0x40, 0x20, 0x1E },  // BF 191
	{ 0x08, 0x46, 0x4A, 0x32, 0x1E },  // C0 192
	{ 0x0A, 0x4A, 0x3E, 0x09, 0x08 },  // C1 193
	{ 0x0E, 0x00, 0x4E, 0x20, 0x1E },  // C2 194
	{ 0x04, 0x45, 0x3D, 0x05, 0x04 },  // C3 195
	{ 0x00, 0x7F, 0x08, 0x10, 0x00 },  // C4 196
	{ 0x44, 0x24, 0x1F, 0x04, 0x04 },  // C5 197
	{ 0x40, 0x42, 0x42, 0x42, 0x40 },  // C6 198
	{ 0x42, 0x2A, 0x12, 0x2A, 0x06 },  // C7 199
	{ 0x22, 0x12, 0x7B, 0x16, 0x22 },  // C8 200
	{ 0x00, 0x40, 0x20, 0x1F, 0x00 },  // C9 201
	{ 0x78, 0x00, 0x02, 0x04, 0x78 },  // CA 202
	{ 0x3F, 0x44, 0x44, 0x44, 0x44 },  // CB 203
	{ 0x02, 0x42, 0x42, 0x22, 0x1E },  // CC 204
	{ 0x04, 0x02, 0x04, 0x08, 0x30 },  // CD 205
	{ 0x32, 0x02, 0x7F, 0x02, 0x32 },  // CE 206
	{ 0x02, 0x12, 0x22, 0x52, 0x0E },  // CF 207
	{ 0x00, 0x2A, 0x2A, 0x2A, 0x40 },  // D0 208
	{ 0x38, 0x24, 0x22, 0x20, 0x70 },  // D1 209
	{ 0x40, 0x28, 0x10, 0x28, 0x06 },  // D2 210
	{ 0x0A, 0x3E, 0x4A, 0x4A, 0x4A },  // D3 211
	{ 0x04, 0x7F, 0x04, 0x14, 0x0C },  // D4 212
	{ 0x40, 0x42, 0x42, 0x7E, 0x40 },  // D5 213
	{ 0x4A, 0x4A, 0x4A, 0x4A, 0x7E },  // D6 214
	{ 0x04, 0x05, 0x45, 0x25, 0x1C },  // D7 215
	{ 0x0F, 0x40, 0x20, 0x1F, 0x00 },  // D8 216
	{ 0x7C, 0x00, 0x7E, 0x40, 0x30 },  // D9 217
	{ 0x7E, 0x40, 0x20, 0x10, 0x08 },  // DA 218
	{ 0x7E, 0x42, 0x42, 0x42, 0x7E },  // DB 219
	{ 0x0E, 0x02, 0x42, 0x22, 0x1E },  // DC 220
	{ 0x42, 0x42, 0x40, 0x20, 0x18 },  // DD 221
	{ 0x02, 0x04, 0x01, 0x02, 0x00 },  // DE 222
	{ 0x07, 0x05, 0x07, 0x00, 0x00 },  // DF 223
	{ 0x38, 0x44, 0x48, 0x30, 0x4C },  // E0 224
	{ 0x20, 0x55, 0x54, 0x55, 0x78 },  // E1 225
	{ 0xF8, 0x54, 0x54, 0x54, 0x28 },  // E2 226
	{ 0x28, 0x54, 0x54, 0x44, 0x20 },  // E3 227
	{ 0xFC, 0x40, 0x40, 0x20, 0x7C },  // E4 228
	{ 0x38, 0x44, 0x4C, 0x54, 0x24 },  // E5 229
	{ 0xF0, 0x48, 0x44, 0x44, 0x38 },  // E6 230
	{ 0x38, 0x44, 0x44, 0x44, 0xFC },  // E7 231
	{ 0x20, 0x40, 0x3C, 0x04, 0x04 },  // E8 232
	{ 0x04, 0x04, 0x00, 0x0E, 0x00 },  // E9 233
	{ 0x00, 0x00, 0x04, 0xFD, 0x00 },  // EA 234
	{ 0x0A, 0x04, 0x0A, 0x00, 0x00 },  // EB 235
	{ 0x18, 0x24, 0x7E, 0x24, 0x10 },  // EC 236
	{ 0x14, 0x7F, 0x54, 0x40, 0x40 },  // ED 237
	{ 0x7C, 0x09, 0x05, 0x05, 0x78 },  // EE 238
	{ 0x38, 0x45, 0x44, 0x45, 0x38 },  // EF 239
	{ 0xFC, 0x48, 0x44, 0x44, 0x38 },  // F0 240
	{ 0x38, 0x44, 0x44, 0x48, 0xFC },  // F1 241
	{ 0x3C, 0x4A, 0x4A, 0x4A, 0x3C },  // F2 242
	{ 0x30, 0x28, 0x10, 0x28, 0x18 },  // F3 243
	{ 0x58, 0x64, 0x04, 0x64, 0x58 },  // F4 244
	{ 0x7C, 0x81, 0x80, 0x41, 0xFC },  // F5 245
	{ 0x63, 0x55, 0x49, 0x41, 0x41 },  // F6 246
	{ 0x44, 0x3C, 0x04, 0x7C, 0x44 },  // F7 247
	{ 0x45, 0x29, 0x11, 0x29, 0x45 },  // F8 248
	{ 0x3C, 0x40, 0x40, 0x40, 0xFC },  // F9 249
	{ 0x14, 0x14, 0x7C, 0x14, 0x12 },  // FA 250
	{ 0x44, 0x3C, 0x14, 0x14, 0x74 },  // FB 251
	{ 0x7C, 0x14, 0x1C, 0x14, 0x7C },  // FC 252
	{ 0x08, 0x08, 0x2A, 0x08, 0x08 },  // FD 253
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },  // FE 254
	{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },  // FF 255
};

// Hitachi HD44780A02
static uint8_t const __code font_A02[240][5] = {
	{ 0x00, 0xFE, 0x7C, 0x38, 0x10 },  // 10  16
	{ 0x10, 0x38, 0x7C, 0xFE, 0x00 },  // 11  17
	{ 0x0C, 0x0A, 0x00, 0x0C, 0x0A },  // 12  18
	{ 0x0A, 0x06, 0x00, 0x0A, 0x06 },  // 13  19
	{ 0x88, 0xCC, 0xEE, 0xCC, 0x88 },  // 14  20
	{ 0x22, 0x66, 0xEE, 0x66, 0x22 },  // 15  21
	{ 0x38, 0x7C, 0x7C, 0x7C, 0x38 },  // 16  22
	{ 0x20, 0x70, 0xA8, 0x20, 0x3E },  // 17  23
	{ 0x08, 0x04, 0xFE, 0x04, 0x08 },  // 18  24
	{ 0x20, 0x40, 0xFE, 0x40, 0x20 },  // 19  25
	{ 0x10, 0x10, 0x54, 0x38, 0x10 },  // 1A  26
	{ 0x10, 0x38, 0x54, 0x10, 0x10 },  // 1B  27
	{ 0x80, 0x88, 0x94, 0xA2, 0x80 },  // 1C  28
	{ 0x80, 0xA2, 0x94, 0x88, 0x80 },  // 1D  29
	{ 0x40, 0x70, 0x7C, 0x70, 0x40 },  // 1E  30
	{ 0x04, 0x1C, 0x7C, 0x1C, 0x04 },  // 1F  31
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },  // 20  32
	{ 0x00, 0x00, 0x9E, 0x00, 0x00 },  // 21  33  !
	{ 0x00, 0x0E, 0x00, 0x0E, 0x00 },  // 22  34  "
	{ 0x28, 0xFE, 0x28, 0xFE, 0x28 },  // 23  35  #
	{ 0x48, 0x54, 0xFE, 0x54, 0x24 },  // 24  36  $
	{ 0x46, 0x26, 0x10, 0xC8, 0xC4 },  // 25  37  %
	{ 0x6C, 0x92, 0xAA, 0x44, 0xA0 },  // 26  38  &
	{ 0x00, 0x0A, 0x06, 0x00, 0x00 },  // 27  39  '
	{ 0x00, 0x38, 0x44, 0x82, 0x00 },  // 28  40  (
	{ 0x00, 0x82, 0x44, 0x38, 0x00 },  // 29  41  )
	{ 0x28, 0x10, 0x7C, 0x10, 0x28 },  // 2A  42  *
	{ 0x10, 0x10, 0x7C, 0x10, 0x10 },  // 2B  43  +
	{ 0x00, 0xA0, 0x60, 0x00, 0x00 },  // 2C  44  ,
	{ 0x10, 0x10, 0x10, 0x10, 0x10 },  // 2D  45  -
	{ 0x00, 0xC0, 0xC0, 0x00, 0x00 },  // 2E  46  .
	{ 0x40, 0x20, 0x10, 0x08, 0x04 },  // 2F  47  /
	{ 0x7C, 0xA2, 0x92, 0x8A, 0x7C },  // 30  48  0
	{ 0x00, 0x84, 0xFE, 0x80, 0x00 },  // 31  49  1
	{ 0x84, 0xC2, 0xA2, 0x92, 0x8C },  // 32  50  2
	{ 0x42, 0x82, 0x8A, 0x96, 0x62 },  // 33  51  3
	{ 0x30, 0x28, 0x24, 0xFE, 0x20 },  // 34  52  4
	{ 0x4E, 0x8A, 0x8A, 0x8A, 0x72 },  // 35  53  5
	{ 0x78, 0x94, 0x92, 0x92, 0x60 },  // 36  54  6
	{ 0x06, 0x02, 0xE2, 0x12, 0x0E },  // 37  55  7
	{ 0x6C, 0x92, 0x92, 0x92, 0x6C },  // 38  56  8
	{ 0x0C, 0x92, 0x92, 0x52, 0x3C },  // 39  57  9
	{ 0x00, 0x6C, 0x6C, 0x00, 0x00 },  // 3A  58  :
	{ 0x00, 0xAC, 0x6C, 0x00, 0x00 },  // 3B  59  ;
	{ 0x10, 0x28, 0x44, 0x82, 0x00 },  // 3C  60  <
	{ 0x28, 0x28, 0x28, 0x28, 0x28 },  // 3D  61  =
	{ 0x00, 0x82, 0x44, 0x28, 0x10 },  // 3E  62  >
	{ 0x04, 0x02, 0xA2, 0x12, 0x0C },  // 3F  63  ?
	{ 0x64, 0x92, 0xF2, 0x82, 0x7C },  // 40  64  @
	{ 0xF8, 0x24, 0x22, 0x24, 0xF8 },  // 41  65  A
	{ 0xFE, 0x92, 0x92, 0x92, 0x6C },  // 42  66  B
	{ 0x7C, 0x82, 0x82, 0x82, 0x44 },  // 43  67  C
	{ 0xFE, 0x82, 0x82, 0x44, 0x38 },  // 44  68  D
	{ 0xFE, 0x92, 0x92, 0x92, 0x82 },  // 45  69  E
	{ 0xFE, 0x12, 0x12, 0x12, 0x02 },  // 46  70  F
	{ 0x7C, 0x82, 0x92, 0x92, 0xF4 },  // 47  71  G
	{ 0xFE, 0x10, 0x10, 0x10, 0xFE },  // 48  72  H
	{ 0x00, 0x82, 0xFE, 0x82, 0x00 },  // 49  73  I
	{ 0x40, 0x80, 0x82, 0x7E, 0x02 },  // 4A  74  J
	{ 0xFE, 0x10, 0x28, 0x44, 0x82 },  // 4B  75  K
	{ 0xFE, 0x80, 0x80, 0x80, 0x80 },  // 4C  76  L
	{ 0xFE, 0x04, 0x18, 0x04, 0xFE },  // 4D  77  M
	{ 0xFE, 0x08, 0x10, 0x20, 0xFE },  // 4E  78  N
	{ 0x7C, 0x82, 0x82, 0x82, 0x7C },  // 4F  79  O
	{ 0xFE, 0x12, 0x12, 0x12, 0x0C },  // 50  80  P
	{ 0x7C, 0x82, 0xA2, 0x42, 0xBC },  // 51  81  Q
	{ 0xFE, 0x12, 0x32, 0x52, 0x8C },  // 52  82  R
	{ 0x4C, 0x92, 0x92, 0x92, 0x64 },  // 53  83  S
	{ 0x02, 0x02, 0xFE, 0x02, 0x02 },  // 54  84  T
	{ 0x7E, 0x80, 0x80, 0x80, 0x7E },  // 55  85  U
	{ 0x3E, 0x40, 0x80, 0x40, 0x3E },  // 56  86  V
	{ 0x7E, 0x80, 0x70, 0x80, 0x7E },  // 57  87  W
	{ 0xC6, 0x28, 0x10, 0x28, 0xC6 },  // 58  88  X
	{ 0x0E, 0x10, 0xE0, 0x10, 0x0E },  // 59  89  Y
	{ 0xC2, 0xA2, 0x92, 0x8A, 0x86 },  // 5A  90  Z
	{ 0x00, 0xFE, 0x82, 0x82, 0x00 },  // 5B  91  [
	{ 0x04, 0x08, 0x10, 0x20, 0x40 },  // 5C  92  '\'
	{ 0x00, 0x82, 0x82, 0xFE, 0x00 },  // 5D  93  ]
	{ 0x08, 0x04, 0x02, 0x04, 0x08 },  // 5E  94  ^
	{ 0x80, 0x80, 0x80, 0x80, 0x80 },  // 5F  95  _
	{ 0x00, 0x02, 0x04, 0x08, 0x00 },  // 60  96  `
	{ 0x40, 0xA8, 0xA8, 0xA8, 0xF0 },  // 61  97  a
	{ 0xFE, 0x90, 0x88, 0x88, 0x70 },  // 62  98  b
	{ 0x70, 0x88, 0x88, 0x88, 0x40 },  // 63  99  c
	{ 0x70, 0x88, 0x88, 0x90, 0xFE },  // 64 100  d
	{ 0x70, 0xA8, 0xA8, 0xA8, 0x30 },  // 65 101  e
	{ 0x10, 0xFC, 0x12, 0x02, 0x04 },  // 66 102  f
	{ 0x10, 0xA8, 0xA8, 0xA8, 0x78 },  // 67 103  g
	{ 0xFE, 0x10, 0x08, 0x08, 0xF0 },  // 68 104  h
	{ 0x00, 0x90, 0xFA, 0x80, 0x00 },  // 69 105  i
	{ 0x40, 0x80, 0x88, 0x7A, 0x00 },  // 6A 106  j
	{ 0xFE, 0x20, 0x50, 0x88, 0x00 },  // 6B 107  k
	{ 0x00, 0x82, 0xFE, 0x80, 0x00 },  // 6C 108  l
	{ 0xF8, 0x08, 0xF0, 0x08, 0xF0 },  // 6D 109  m
	{ 0xF8, 0x10, 0x08, 0x08, 0xF0 },  // 6E 110  n
	{ 0x70, 0x88, 0x88, 0x88, 0x70 },  // 6F 111  o
	{ 0xF8, 0x28, 0x28, 0x28, 0x10 },  // 70 112  p
	{ 0x10, 0x28, 0x28, 0x30, 0xF8 },  // 71 113  q
	{ 0xF8, 0x10, 0x08, 0x08, 0x10 },  // 72 114  r
	{ 0x90, 0xA8, 0xA8, 0xA8, 0x40 },  // 73 115  s
	{ 0x08, 0x7E, 0x88, 0x80, 0x40 },  // 74 116  t
	{ 0x78, 0x80, 0x80, 0x40, 0xF8 },  // 75 117  u
	{ 0x38, 0x40, 0x80, 0x40, 0x38 },  // 76 118  v
	{ 0x78, 0x80, 0x60, 0x80, 0x78 },  // 77 119  w
	{ 0x88, 0x50, 0x20, 0x50, 0x88 },  // 78 120  x
	{ 0x18, 0xA0, 0xA0, 0xA0, 0x78 },  // 79 121  y
	{ 0x88, 0xC8, 0xA8, 0x98, 0x88 },  // 7A 122  z
	{ 0x00, 0x10, 0x6C, 0x82, 0x00 },  // 7B 123  {
	{ 0x00, 0x00, 0xFE, 0x00, 0x00 },  // 7C 124  |
	{ 0x00, 0x82, 0x6C, 0x10, 0x00 },  // 7D 125  }
	{ 0x20, 0x10, 0x10, 0x20, 0x10 },  // 7E 126  ~
	{ 0x78, 0x44, 0x42, 0x44, 0x78 },  // 7F 127
	{ 0xFE, 0x92, 0x92, 0x92, 0x66 },  // 80 128
	{ 0xF0, 0x29, 0x27, 0x21, 0xFF },  // 81 129
	{ 0xEE, 0x10, 0xFE, 0x10, 0xEE },  // 82 130
	{ 0x82, 0x82, 0x92, 0x92, 0x6C },  // 83 131
	{ 0xFE, 0x20, 0x10, 0x08, 0xFE },  // 84 132
	{ 0xFC, 0x41, 0x22, 0x11, 0xFC },  // 85 133
	{ 0x40, 0x82, 0x7E, 0x02, 0xFE },  // 86 134
	{ 0xFE, 0x02, 0x02, 0x02, 0xFE },  // 87 135
	{ 0x8E, 0x50, 0x20, 0x10, 0x0E },  // 88 136
	{ 0x7E, 0x40, 0x40, 0x40, 0xFE },  // 89 137
	{ 0x0E, 0x10, 0x10, 0x10, 0xFE },  // 8A 138
	{ 0xFC, 0x80, 0xFC, 0x80, 0xFC },  // 8B 139
	{ 0x7E, 0x40, 0x7E, 0x40, 0xFE },  // 8C 140
	{ 0x02, 0xFE, 0x90, 0x90, 0x60 },  // 8D 141
	{ 0xFE, 0x90, 0x60, 0x00, 0xFE },  // 8E 142
	{ 0x44, 0x92, 0x8A, 0x92, 0x7C },  // 8F 143
	{ 0x70, 0x88, 0x90, 0x60, 0x98 },  // 90 144
	{ 0xC0, 0xC0, 0xFE, 0x04, 0x18 },  // 91 145
	{ 0xFE, 0x02, 0x02, 0x02, 0x06 },  // 92 146
	{ 0x88, 0x78, 0x08, 0xF8, 0x88 },  // 93 147
	{ 0xC6, 0xAA, 0x92, 0x82, 0x82 },  // 94 148
	{ 0x70, 0x88, 0x88, 0x78, 0x08 },  // 95 149
	{ 0x60, 0x60, 0x3F, 0xC5, 0xFE },  // 96 150
	{ 0x10, 0x08, 0x78, 0x88, 0x04 },  // 97 151
	{ 0x20, 0x3C, 0x7E, 0x3C, 0x20 },  // 98 152
	{ 0x7C, 0x92, 0x92, 0x92, 0x7C },  // 99 153
	{ 0xB8, 0xC4, 0x04, 0xC4, 0xB8 },  // 9A 154
	{ 0x60, 0x94, 0x8A, 0x92, 0x64 },  // 9B 155
	{ 0x30, 0x28, 0x10, 0x28, 0x18 },  // 9C 156
	{ 0x38, 0x7C, 0xF8, 0x7C, 0x38 },  // 9D 157
	{ 0x50, 0xA8, 0xA8, 0x88, 0x40 },  // 9E 158
	{ 0xFC, 0x02, 0x02, 0x02, 0xFC },  // 9F 159
	{ 0xFE, 0xFE, 0x00, 0xFE, 0xFE },  // A0 160
	{ 0x00, 0x00, 0xF2, 0x00, 0x00 },  // A1 161
	{ 0x38, 0x44, 0xFE, 0x44, 0x20 },  // A2 162
	{ 0x90, 0x7C, 0x92, 0x82, 0x40 },  // A3 163
	{ 0x44, 0x38, 0x28, 0x38, 0x44 },  // A4 164
	{ 0x2A, 0x2C, 0xF8, 0x2C, 0x2A },  // A5 165
	{ 0x00, 0x00, 0xEE, 0x00, 0x00 },  // A6 166
	{ 0x40, 0x94, 0xAA, 0x52, 0x04 },  // A7 167
	{ 0x50, 0x90, 0x7C, 0x12, 0x14 },  // A8 168
	{ 0xFE, 0x82, 0xBA, 0x92, 0xFE },  // A9 169
	{ 0x90, 0xAA, 0xAA, 0xAA, 0xBC },  // AA 170
	{ 0x10, 0x28, 0x54, 0x28, 0x44 },  // AB 171
	{ 0xFE, 0x10, 0x7C, 0x82, 0x7C },  // AC 172
	{ 0x8C, 0x52, 0x32, 0x12, 0xFE },  // AD 173
	{ 0xFE, 0x82, 0xCA, 0xA2, 0xFE },  // AE 174
	{ 0x00, 0x0C, 0x0A, 0x00, 0x00 },  // AF 175
	{ 0x0E, 0x11, 0x11, 0x0E, 0x00 },  // B0 176
	{ 0x88, 0x88, 0xBE, 0x88, 0x88 },  // B1 177
	{ 0x12, 0x19, 0x15, 0x12, 0x00 },  // B2 178
	{ 0x11, 0x15, 0x15, 0x0A, 0x00 },  // B3 179
	{ 0x7F, 0x05, 0x25, 0xF2, 0xA0 },  // B4 180
	{ 0xFE, 0x20, 0x20, 0x10, 0x3E },  // B5 181
	{ 0x0C, 0x12, 0x12, 0xFE, 0xFE },  // B6 182
	{ 0x00, 0x30, 0x30, 0x00, 0x00 },  // B7 183
	{ 0x70, 0x88, 0x60, 0x88, 0x70 },  // B8 184
	{ 0x12, 0x1F, 0x10, 0x00, 0x00 },  // B9 185
	{ 0x9C, 0xA2, 0xA2, 0xA2, 0x9C },  // BA 186
	{ 0x44, 0x28, 0x54, 0x28, 0x10 },  // BB 187
	{ 0x17, 0x68, 0x54, 0xFA, 0x41 },  // BC 188
	{ 0x17, 0x08, 0x94, 0xCA, 0xB1 },  // BD 189
	{ 0x15, 0x1F, 0x60, 0x50, 0xF8 },  // BE 190
	{ 0x60, 0x90, 0x8A, 0x80, 0x40 },  // BF 191
	{ 0xF0, 0x29, 0x26, 0x28, 0xF0 },  // C0 192
	{ 0xF0, 0x28, 0x26, 0x29, 0xF0 },  // C1 193
	{ 0xF0, 0x2A, 0x29, 0x2A, 0xF0 },  // C2 194
	{ 0xF2, 0x29, 0x29, 0x2A, 0xF1 },  // C3 195
	{ 0xF0, 0x29, 0x24, 0x29, 0xF0 },  // C4 196
	{ 0xF0, 0x2A, 0x2D, 0x2A, 0xF0 },  // C5 197
	{ 0xF8, 0x24, 0xFE, 0x92, 0x92 },  // C6 198
	{ 0x1E, 0x21, 0xA1, 0xE1, 0x12 },  // C7 199
	{ 0xF8, 0xA9, 0xAA, 0xA8, 0x88 },  // C8 200
	{ 0xF8, 0xA8, 0xAA, 0xA9, 0x88 },  // C9 201
	{ 0xF8, 0xAA, 0xA9, 0xAA, 0x88 },  // CA 202
	{ 0xF8, 0xAA, 0xA8, 0xAA, 0x88 },  // CB 203
	{ 0x00, 0x89, 0xFA, 0x88, 0x00 },  // CC 204
	{ 0x00, 0x88, 0xFA, 0x89, 0x00 },  // CD 205
	{ 0x00, 0x8A, 0xF9, 0x8A, 0x00 },  // CE 206
	{ 0x00, 0x8A, 0xF8, 0x8A, 0x00 },  // CF 207
	{ 0x10, 0xFE, 0x92, 0x82, 0x7C },  // D0 208
	{ 0xFA, 0x11, 0x21, 0x42, 0xF9 },  // D1 209
	{ 0x78, 0x85, 0x86, 0x84, 0x78 },  // D2 210
	{ 0x78, 0x84, 0x86, 0x85, 0x78 },  // D3 211
	{ 0x70, 0x8A, 0x89, 0x8A, 0x70 },  // D4 212
	{ 0x72, 0x89, 0x89, 0x8A, 0x71 },  // D5 213
	{ 0x78, 0x85, 0x84, 0x85, 0x78 },  // D6 214
	{ 0x44, 0x28, 0x10, 0x28, 0x44 },  // D7 215
	{ 0x10, 0xAA, 0xFE, 0xAA, 0x10 },  // D8 216
	{ 0x7C, 0x81, 0x82, 0x80, 0x7C },  // D9 217
	{ 0x7C, 0x80, 0x82, 0x81, 0x7C },  // DA 218
	{ 0x78, 0x82, 0x81, 0x82, 0x78 },  // DB 219
	{ 0x7C, 0x81, 0x80, 0x81, 0x7C },  // DC 220
	{ 0x04, 0x08, 0xF2, 0x09, 0x04 },  // DD 221
	{ 0x81, 0xFF, 0xA4, 0x24, 0x18 },  // DE 222
	{ 0x80, 0x7C, 0x92, 0x92, 0x6C },  // DF 223
	{ 0x40, 0xA9, 0xAA, 0xA8, 0xF0 },  // E0 224
	{ 0x40, 0xA8, 0xAA, 0xA9, 0xF0 },  // E1 225
	{ 0x40, 0xAA, 0xA9, 0xAA, 0xF0 },  // E2 226
	{ 0x42, 0xA9, 0xA9, 0xAA, 0xF1 },  // E3 227
	{ 0x40, 0xAA, 0xA8, 0xAA, 0xF0 },  // E4 228
	{ 0x40, 0xAA, 0xAD, 0xAA, 0xF0 },  // E5 229
	{ 0x64, 0x94, 0x78, 0x94, 0x58 },  // E6 230
	{ 0x18, 0xA4, 0xE4, 0x24, 0x10 },  // E7 231
	{ 0x70, 0xA9, 0xAA, 0xA8, 0x30 },  // E8 232
	{ 0x70, 0xA8, 0xAA, 0xA9, 0x30 },  // E9 233
	{ 0x70, 0xAA, 0xA9, 0xAA, 0x30 },  // EA 234
	{ 0x70, 0xAA, 0xA8, 0xAA, 0x30 },  // EB 235
	{ 0x00, 0x91, 0xFA, 0x80, 0x00 },  // EC 236
	{ 0x00, 0x90, 0xFA, 0x81, 0x00 },  // ED 237
	{ 0x00, 0x92, 0xF9, 0x82, 0x00 },  // EE 238
	{ 0x00, 0x92, 0xF8, 0x82, 0x00 },  // EF 239
	{ 0x4A, 0xA4, 0xAA, 0xB0, 0x60 },  // F0 240
	{ 0xFA, 0x11, 0x09, 0x0A, 0xF1 },  // F1 241
	{ 0x70, 0x89, 0x8A, 0x88, 0x70 },  // F2 242
	{ 0x70, 0x88, 0x8A, 0x89, 0x70 },  // F3 243
	{ 0x60, 0x94, 0x92, 0x94, 0x60 },  // F4 244
	{ 0x64, 0x92, 0x92, 0x94, 0x62 },  // F5 245
	{ 0x70, 0x8A, 0x88, 0x8A, 0x70 },  // F6 246
	{ 0x10, 0x10, 0x54, 0x10, 0x10 },  // F7 247
	{ 0x10, 0xA8, 0x7C, 0x2A, 0x10 },  // F8 248
	{ 0x78, 0x81, 0x82, 0x40, 0xF8 },  // F9 249
	{ 0x78, 0x80, 0x82, 0x41, 0xF8 },  // FA 250
	{ 0x78, 0x82, 0x81, 0x42, 0xF8 },  // FB 251
	{ 0x78, 0x82, 0x80, 0x42, 0xF8 },  // FC 252
	{ 0x18, 0xA0, 0xA4, 0xA2, 0x78 },  // FD 253
	{ 0x00, 0x82, 0xFE, 0xA8, 0x10 },  // FE 254
	{ 0x18, 0xA2, 0xA0, 0xA2, 0x78 },  // FF 255
};