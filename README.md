# perfectbitsequence
Perfect Bit Sequence

# Combining Numbers with Fusion

With this algorithm, a group of numbers searches for the best combination that can be made through fusion.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Flexible and Scalable:** Easily adaptable to different datasets and applications.
- **Open Source:** Open to community contributions and continuously being developed.

## Installation

### Requirements

- **CMake**: Version 3.10 or higher
- **C++ Compiler**: Supporting C++11 or higher (e.g., GCC, Clang, MSVC)

### Steps

1. **Clone the Repository:**
    ```bash
    git clone https://github.com/azizgokhannarin/perfectbitsequence.git
    cd perfectbitsequence
    ```
2. **Create a Build Directory:**
    ```bash
    mkdir build
    cd build
    ```

3. **Configure the Project with CMake:**
    ```bash
    cmake ..
    ```
    *If you need to specify custom installation paths or enable/disable features, you can pass additional flags to CMake. For example:*
    ```bash
    cmake -DCMAKE_INSTALL_PREFIX=/desired/install/path -DENABLE_ASSIMP=ON ..
    ```

4. **Build the Project:**
    ```bash
    cmake --build .
    ```
    *Alternatively, you can use make or your preferred build system:*
    ```bash
    make
    ```

5. **Install the Project (Optional):**
    ```bash
    cmake --install .
    ```
    *This step installs the built binaries and resources to the specified installation directory.*

## Usage

In the example, it produces a 263-bit output, where the last 7 bits are a repetition of the first 7 bits, forming a circular sequence. As a result, all values between 0 and 255 can be represented within 256 bits, equivalent to 32 bytes. This represents the optimal value for this fusion process.

For example, in the following part, you can see the new sequence of numbers between 0-255 that have been subjected to some kind of encoding process.

## Examples
Below you can see the result of the best combination of bits.

11111111000000001000000110000010100000111000010010000101100001101000011110001000100110001010100010111000110010001101100011101000111110010010100100111001010110010110100101111001100110101001101110011101100111101001111110101010111010110110101111101101111011101111111

This operation produces a 263-bit output, where the last 7 bits are a repetition of the first 7 bits, forming a circular sequence. As a result, all values between 0 and 255 can be represented within 256 bits, equivalent to 32 bytes. This represents the optimal value for this fusion process.
Below you can see the new sequence of numbers between 0-255.

255
254
252
248
240
224
192
128
0
1
2
4
8
16
32
64
129
3
6
12
24
48
96
193
130
5
10
20
40
80
160
65
131
7
14
28
56
112
225
194
132
9
18
36
72
144
33
66
133
11
22
44
88
176
97
195
134
13
26
52
104
208
161
67
135
15
30
60
120
241
226
196
136
17
34
68
137
19
38
76
152
49
98
197
138
21
42
84
168
81
162
69
139
23
46
92
184
113
227
198
140
25
50
100
200
145
35
70
141
27
54
108
216
177
99
199
142
29
58
116
232
209
163
71
143
31
62
124
249
242
228
201
146
37
74
148
41
82
164
73
147
39
78
156
57
114
229
202
149
43
86
172
89
178
101
203
150
45
90
180
105
210
165
75
151
47
94
188
121
243
230
204
153
51
102
205
154
53
106
212
169
83
166
77
155
55
110
220
185
115
231
206
157
59
118
236
217
179
103
207
158
61
122
244
233
211
167
79
159
63
126
253
250
245
234
213
170
85
171
87
174
93
186
117
235
214
173
91
182
109
218
181
107
215
175
95
190
125
251
246
237
219
183
111
222
189
123
247
238
221
187
119
239
223
191
127

### Simple Byte Data

## Contributing

We welcome your contributions! To contribute to the project, follow these steps:

1. **Fork the Repository:** Fork the project repository on GitHub.
2. **Create a New Branch:** 
    ```bash
    git checkout -b feature/FeatureName
    ```
3. **Make Your Changes:** Add or fix code as needed.
4. **Commit Your Changes:** 
    ```bash
    git commit -m "Descriptive commit message"
    ```
5. **Push to the Branch:** 
    ```bash
    git push origin feature/FeatureName
    ```
6. **Open a Pull Request:** Submit a pull request to integrate your changes into the main repository.

## License

This project is licensed under the [Apache 2.0](LICENSE). For more details, please refer to the `LICENSE` file.
