<div align="center">

# 🗺️ FdF - Fil de Fer

### Wireframe 3D Landscape Renderer

<p>
  <img src="https://img.shields.io/badge/Score-100%2F100-success?style=for-the-badge&logo=42" alt="42 Score"/>
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Language"/>
  <img src="https://img.shields.io/badge/Graphics-MiniLibX-FF6B6B?style=for-the-badge" alt="MiniLibX"/>
  <img src="https://img.shields.io/badge/42-Urduliz-000000?style=for-the-badge&logo=42&logoColor=white" alt="42 Urduliz"/>
</p>

*A 3D wireframe viewer that transforms height maps into isometric projections using MiniLibX graphics library.*

[Installation](#%EF%B8%8F-installation) • [Usage](#-usage) • [Map Format](#-map-format) • [How It Works](#-how-it-works) • [Technical Details](#-technical-details)

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Installation](#%EF%B8%8F-installation)
- [Usage](#-usage)
- [Map Format](#-map-format)
- [How It Works](#-how-it-works)
- [Project Structure](#-project-structure)
- [Technical Details](#-technical-details)
- [What I Learned](#-what-i-learned)
- [License](#-license)

---

## 🎯 About the Project

**FdF (Fil de Fer - Wireframe)** is a graphics programming project that creates 3D wireframe representations of relief landscapes. The program reads a height map from a file and renders it in **isometric projection**, connecting points in 3D space with lines.

### Key Features

<table>
<tr>
<td width="50%" valign="top">

### 📖 Core Functionality
- Reads and parses `.fdf` map files
- Handles maps of any size (minimum 2x2)
- Dynamic memory allocation for matrices
- Comprehensive error handling and validation

</td>
<td width="50%" valign="top">

### ⚡ Rendering Engine
- Isometric projection (0.7 radians ≈ 40°)
- Bresenham's line drawing algorithm
- Resolution: 1920x1080 (Full HD)
- White wireframe (0x00FFFFFF)

</td>
</tr>
<tr>
<td width="50%" valign="top">

### 🎯 Visual Features
- Altitude-based scaling (z * 5)
- Custom projection offsets (600, -450)
- Screen clipping for window bounds
- Smooth line rendering

</td>
<td width="50%" valign="top">

### 🛡️ Controls & Interface
- ESC key (53) to exit
- Single-argument command line
- Clear error messages
- Efficient event loop

</td>
</tr>
</table>

---

## 🛠️ Installation

### Prerequisites

- **GCC** or **Clang** compiler
- **Make**
- **MiniLibX** (included in `mlx/` directory)
- **libft** (included in `libft/` directory)
- Unix-based system (Linux, macOS)

### Clone and Compile

```bash
# Clone the repository
git clone https://github.com/Z3n42/fdf.git
cd fdf

# Compile the project
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile from scratch
make re
```

After running `make`, an `fdf` executable will be created and ready to use.

---

## 🚀 Usage

### Basic Execution

```bash
# Run with a map file
./fdf test_maps/[map_name].fdf

# Example
./fdf test_maps/42.fdf
```

### Command-Line Arguments

The program expects exactly **one argument**: the path to a `.fdf` map file.

```bash
# Correct usage
./fdf test_maps/42.fdf

# Error cases
./fdf                          # Error: No map provided
./fdf map1.fdf map2.fdf       # Error: Too many arguments
./fdf nonexistent.fdf         # Error: Cannot open file
```

### Controls

| Key | Code | Action |
|-----|------|--------|
| **ESC** | 53 | Close window and exit program |

---

## 📄 Map Format

Maps are stored in `.fdf` files with a simple grid format representing height values.

### Basic Structure

```
0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  0  0  0
0  0  1  2  2  2  1  0  0  0
0  0  1  2  3  2  1  0  0  0
0  0  1  2  2  2  1  0  0  0
0  0  1  1  1  1  1  0  0  0
0  0  0  0  0  0  0  0  0  0
```

### Format Rules

- Each number represents a point's **altitude (Z coordinate)**
- Numbers separated by **spaces**
- **Horizontal position** = X coordinate (column index)
- **Vertical position** = Y coordinate (row index)
- Minimum map size: **2x2**
- Maximum: limited by available memory

### Error Handling

The program validates:
- File existence and readability
- Minimum map dimensions (2x2)
- Valid format (numbers separated by spaces)

Error message: `Map Error` followed by program exit.

---

## 🎨 How It Works

### From Map to Wireframe

Visualization of how a simple pyramid transforms into a 3D wireframe:

<details>
<summary><b>Step 1: Input Map</b></summary>

```
Map file (pyramid.fdf):
0  0  0  0  0
0  1  1  1  0
0  1  2  1  0
0  1  1  1  0
0  0  0  0  0

Grid Interpretation:
  X: 0 1 2 3 4
Y
0   • • • • •
1   • • • • •
2   • • • • •
3   • • • • •
4   • • • • •

Heights:
0 0 0 0 0
0 1 1 1 0
0 1 2 1 0  ← (2,2) = peak at height 2
0 1 1 1 0
0 0 0 0 0
```

</details>

<details>
<summary><b>Step 2: 3D Space Interpretation</b></summary>

```
Each point (x, y) from map gets a height z:
- Point (2, 2) → height 2 (peak)
- Point (1, 2) → height 1
- Point (0, 0) → height 0 (ground)

Side View (looking from X axis):
    2   •              ← Peak
    1   • • •          ← Mid level  
    0   • • • • •      ← Ground
        ─────────
        0 1 2 3 4 (X)

This creates a 3D landscape in memory.
```

</details>

<details>
<summary><b>Step 3: Isometric Projection</b></summary>

```
Transformation formulas (from code):
xb = (x - y) * cos(0.7) + 600
yb = (y + x) * sin(0.7) - 450 - z * 5

Parameters:
- Angle: 0.7 radians ≈ 40°
- cos(0.7) ≈ 0.765
- sin(0.7) ≈ 0.644
- Offset: (600, -450) for centering
- Z scale: z * 5 for visibility

Result (ASCII approximation):
       •           ← (2,2,2) Peak
      /│\
     • • •         ← Height 1 ring
    /│ │ │\
   • • • • •       ← Ground level

Legend:
• = Vertex (point)
│ = Vertical line
/ \ = Diagonal lines connecting points
```

</details>

### Algorithm Flow

```
┌─────────────────────────────────────────────────────────┐
│                   FdF Rendering Pipeline                 │
└─────────────────────────────────────────────────────────┘
                           │
                           ▼
                 ┌──────────────────┐
                 │   1. Parse Map   │
                 └──────────────────┘
                           │
         ┌─────────────────┼─────────────────┐
         ▼                 ▼                 ▼
   ft_xcount()       ft_open()        ft_matrix()
   Count columns   Validate dims   Create 2D array
         │                 │                 │
         └─────────────────┴─────────────────┘
                           │
                           ▼
              ┌─────────────────────────┐
              │ 2. Initialize Graphics  │
              └─────────────────────────┘
                           │
         ┌─────────────────┼─────────────────┐
         ▼                 ▼                 ▼
   mlx_init()      mlx_new_window()   mlx_new_image()
   Start MLX      (1920x1080)         Create buffer
         │                 │                 │
         └─────────────────┴─────────────────┘
                           │
                           ▼
                ┌────────────────────┐
                │ 3. Draw Wireframe  │
                └────────────────────┘
                           │
         ┌─────────────────┴─────────────────┐
         ▼                                   ▼
   ft_draw_x()                         ft_draw_y()
   Connect horizontal                  Connect vertical
   lines (row by row)                  lines (col by col)
         │                                   │
         └──────────┬────────────────────────┘
                    ▼
            ft_brasenham()
            ┌──────┴──────┐
            ▼             ▼
      ft_plotlow()   ft_plothigh()
      (slope < 1)    (slope ≥ 1)
            │             │
            └──────┬──────┘
                   ▼
          my_mlx_pixel_put()
          Draw white pixels
                   │
                   ▼
        ┌────────────────────┐
        │ 4. Display & Wait  │
        └────────────────────┘
                   │
    ┌──────────────┼──────────────┐
    ▼              ▼              ▼
mlx_put_image  mlx_key_hook  mlx_loop()
Display        Listen ESC    Event loop
```

---

## 📁 Project Structure

```
fdf/
├── 📄 Makefile              # Build configuration
├── 📄 fdf.h                 # Header with structs and prototypes
├── 📄 LICENSE               # MIT License
│
├── 📄 fdf.c                 # Main: parsing and initialization (~90 lines)
├── 📄 draw2.c               # Drawing functions (~110 lines)
├── 📄 drw_aux.c             # Bresenham algorithm (~80 lines)
│
├── 📂 libft/                # Custom C library
│   ├── libft.h
│   ├── ft_atoi.c
│   ├── ft_split.c
│   └── ... (other libft functions)
│
├── 📂 mlx/                  # MiniLibX graphics library
│   ├── mlx.h
│   ├── libmlx.a
│   └── ... (MLX source files)
│
└── 📂 test_maps/            # Example .fdf map files
    ├── 42.fdf
    ├── pyramid.fdf
    └── ... (various test maps)
```

### File Descriptions

| File | Lines | Purpose |
|------|-------|---------|
| `fdf.c` | ~90 | Entry point, map parsing, matrix creation, main loop |
| `draw2.c` | ~110 | Rendering functions: `ft_draw()`, `ft_draw_x()`, `ft_draw_y()` |
| `drw_aux.c` | ~80 | Bresenham: `ft_brasenham()`, `ft_plotlow()`, `ft_plothigh()` |
| `fdf.h` | ~50 | Struct definitions and function prototypes |

---

## 🔧 Technical Details

### Data Structures

The implementation uses three main structures:

<details>
<summary><b>t_data - MiniLibX Graphics Context</b></summary>

```c
typedef struct s_data {
    void        *mlx;      // MLX instance pointer
    void        *mlx_win;  // Window pointer
    void        *img;      // Image pointer
    char        *addr;     // Image data address
    int         bits;      // Bits per pixel
    int         line;      // Line size in bytes
    int         end;       // Endianness
    uintptr_t   col;       // Color value (0x00FFFFFF)
} t_data;
```

**Purpose:** Manages all MiniLibX-related data for window and image manipulation.

**Key Fields:**
- `addr`: Direct access to pixel buffer for fast drawing
- `col`: Fixed white color for all lines

</details>

<details>
<summary><b>t_cord - Coordinate System</b></summary>

```c
typedef struct s_cord {
    int x, x1;      // Original X coordinates (map space)
    int y, y1;      // Original Y coordinates (map space)
    int xb, xb1;    // Transformed screen X (after isometric)
    int yb, yb1;    // Transformed screen Y (after isometric)
    int z, z1;      // Z height values from map
    int dx, dy;     // Bresenham deltas
    int p;          // Bresenham decision parameter
    int xi, yi;     // Bresenham increments
    int av, ve;     // Loop counters for iteration
} t_cord;
```

**Purpose:** Stores coordinate pairs and Bresenham algorithm state.

**Coordinate Spaces:**
- Map space: `(x, y, z)` from file
- Screen space: `(xb, yb)` after projection

</details>

<details>
<summary><b>t_a - Map Data Container</b></summary>

```c
typedef struct s_a {
    int     x;      // Map width (number of columns)
    int     y;      // Map height (number of rows)
    int     fd;     // File descriptor for reading
    char    *tab;   // Temporary line buffer
    int     **m;    // 2D matrix of height values
} t_a;
```

**Purpose:** Holds parsed map data and dimensions.

**Memory Management:**
- `m`: Dynamically allocated 2D array
- Each `m[i]` is a row of integers

</details>

### Isometric Projection

<details>
<summary><b>Projection Formula Implementation</b></summary>

```c
// From ft_draw_x() and ft_draw_y() in draw2.c
xb = (x - y) * cos(0.7) + 600;
yb = (y + x) * sin(0.7) - 450 - z * 5;
```

**Parameters Breakdown:**

| Parameter | Value | Purpose |
|-----------|-------|---------|
| Angle | 0.7 rad ≈ 40° | Isometric view angle |
| cos(0.7) | ≈ 0.765 | Horizontal compression |
| sin(0.7) | ≈ 0.644 | Vertical compression |
| X offset | +600 | Horizontal centering |
| Y offset | -450 | Vertical centering |
| Z scale | × 5 | Amplify height differences |

**Why 0.7 radians?**
- Standard isometric uses 30° (0.523 rad)
- This implementation uses 40° for slightly more top-down view
- Result: Better visibility of height variations

**Why z × 5?**
- Raw Z values often too small to see
- Factor of 5 makes elevation changes visible
- Balances between flat and overly steep appearance

</details>

### Bresenham's Line Algorithm

<details>
<summary><b>ft_plotlow() - Shallow Lines (|slope| < 1)</b></summary>

```c
void ft_plotlow(t_data *img, t_cord *c)
{
    int dx, dy, p, yi;

    dx = c->xb1 - c->xb;
    dy = c->yb1 - c->yb;
    yi = 1;

    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    p = 2 * (dy - dx);

    while (c->xb++ < c->xb1)
    {
        // Screen clipping
        if (c->xb < 1919 && c->yb < 1079 && c->xb > 0 && c->yb > 0)
            my_mlx_pixel_put(img, c->xb, c->yb, 0x00FFFFFF);

        if (p > 0)
        {
            c->yb += yi;
            p += 2 * (dy - dx);
        }
        else
            p += 2 * dy;
    }
}
```

**Algorithm Characteristics:**
- Integer-only arithmetic (no floating point)
- Iterates along X axis
- Decision parameter `p` determines when to step in Y
- Handles both positive and negative slopes

**Screen Clipping:**
- X range: 0 to 1919
- Y range: 0 to 1079
- Prevents drawing outside window bounds

</details>

<details>
<summary><b>ft_plothigh() - Steep Lines (|slope| ≥ 1)</b></summary>

```c
void ft_plothigh(t_data *img, t_cord *c)
{
    int dx, dy, p, xi;

    dx = c->xb1 - c->xb;
    dy = c->yb1 - c->yb;
    xi = 1;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    p = 2 * (dx - dy);

    while (c->yb++ < c->yb1)
    {
        // Screen clipping
        if (c->xb < 1919 && c->yb < 1079 && c->xb > 0 && c->yb > 0)
            my_mlx_pixel_put(img, c->xb, c->yb, 0x00FFFFFF);

        if (p > 0)
        {
            c->xb += xi;
            p += 2 * (dx - dy);
        }
        else
            p += 2 * dx;
    }
}
```

**Key Difference from ft_plotlow:**
- Iterates along Y axis instead of X
- Ensures smooth lines for steep slopes
- Same integer-only approach

**Why Two Functions?**
- Bresenham requires iteration along major axis
- Slope < 1: X is major axis (use plotlow)
- Slope ≥ 1: Y is major axis (use plothigh)

</details>

### Map Parsing

<details>
<summary><b>ft_xcount() - Column Counter</b></summary>

```c
int ft_xcount(char const *s, char c)
{
    int counter = 0;
    int pos = 0;

    while (s[counter])
    {
        if (s[counter] == c && s[counter + 1] != c)
            pos++;
        counter++;
    }

    return (s[counter - 1] == ' ') ? pos : pos + 1;
}
```

**Purpose:** Count number of columns in a map row.

**Logic:**
- Counts transitions from space to non-space
- Handles trailing spaces correctly
- Returns accurate column count

</details>

<details>
<summary><b>ft_matrix() - 2D Array Creation</b></summary>

```c
int **ft_matrix(int fd, int x, int y)
{
    int     **mat;
    char    *str;
    char    **tbl;
    int     j;
    int     i;

    mat = (int **)malloc(y * sizeof(int *));
    j = 0;

    while (get_next_line(fd, &str))
    {
        tbl = ft_split(str, ' ');
        mat[j] = (int *)malloc(x * sizeof(int));

        for (i = 0; tbl[i]; i++)
            mat[j][i] = ft_atoi(tbl[i]);

        // Free temporary allocations
        free(str);
        // (free tbl and its elements)
        j++;
    }

    return mat;
}
```

**Process:**
1. Allocate array of row pointers
2. For each line:
   - Read with `get_next_line()`
   - Split by spaces with `ft_split()`
   - Allocate row array
   - Convert strings to integers with `ft_atoi()`
3. Return complete 2D array

</details>

### Drawing Strategy

<details>
<summary><b>ft_draw_x() - Horizontal Connections</b></summary>

```c
void ft_draw_x(t_data *img, t_a *a)
{
    // For each row (y):
    //   For each point in row (x):
    //     - Get current point (x, y, z)
    //     - Get next point (x+1, y, z1)
    //     - Apply isometric transformation to both
    //     - Call ft_brasenham to draw line
    //     - Continue until end of row
}
```

**Result:** All horizontal lines connecting adjacent points in same row.

</details>

<details>
<summary><b>ft_draw_y() - Vertical Connections</b></summary>

```c
void ft_draw_y(t_data *img, t_a *a)
{
    // For each column (x):
    //   For each point in column (y):
    //     - Get current point (x, y, z)
    //     - Get next point (x, y+1, z1)
    //     - Apply isometric transformation to both
    //     - Call ft_brasenham to draw line
    //     - Continue until end of column
}
```

**Result:** All vertical lines connecting adjacent points in same column.

**Combined:** `ft_draw_x()` + `ft_draw_y()` = complete wireframe mesh.

</details>

---

## 💡 What I Learned

Through this project, deep understanding was gained of:

- ✅ **Computer Graphics Fundamentals**: Rasterization, projection formulas, pixel manipulation
- ✅ **MiniLibX Library**: Window creation, image manipulation, pixel buffer management
- ✅ **Bresenham's Algorithm**: Integer-only line drawing for efficiency and accuracy
- ✅ **Isometric Projection**: Converting 3D world coordinates to 2D screen space
- ✅ **File Parsing**: Reading and validating structured text files with `get_next_line`
- ✅ **2D Array Management**: Dynamic allocation, indexing, and proper memory cleanup
- ✅ **Linear Algebra**: Trigonometric transformations using cos/sin functions
- ✅ **Memory Management**: Handling complex nested structures and preventing leaks
- ✅ **Event Handling**: Implementing keyboard hooks with MiniLibX event system

### Key Challenges

<table>
<tr>
<th>Challenge</th>
<th>Solution</th>
</tr>
<tr>
<td><b>Understanding Isometric Math</b></td>
<td>Studied projection formulas, experimented with angles (0.7 rad), and tuned offsets (600, -450) for optimal view</td>
</tr>
<tr>
<td><b>Bresenham Implementation</b></td>
<td>Separated into plotlow/plothigh for different slopes, used integer-only arithmetic for performance</td>
</tr>
<tr>
<td><b>Map Parsing</b></td>
<td>Created ft_xcount for accurate column counting, ft_matrix for dynamic 2D array creation</td>
</tr>
<tr>
<td><b>Coordinate Systems</b></td>
<td>Managed multiple spaces (map, world, screen) with clear variable naming (x/y/z vs xb/yb)</td>
</tr>
<tr>
<td><b>Memory Leaks</b></td>
<td>Careful freeing of 2D arrays, MLX resources, and temporary buffers from get_next_line</td>
</tr>
<tr>
<td><b>Screen Clipping</b></td>
<td>Added bounds checking (0-1919, 0-1079) in plotlow/plothigh to prevent segfaults</td>
</tr>
</table>

### Design Decisions

**Why 0.7 radians instead of standard 0.523 (30°)?**
- Provides slightly more top-down view (40° vs 30°)
- Better visibility of height variations
- More aesthetically pleasing for landscape maps

**Why Z scaling factor of 5?**
- Raw Z values (0-10) too small to see differences
- Factor of 5 creates visible elevation without distortion
- Balanced between flat appearance and excessive steepness

**Why 1920x1080 resolution?**
- Full HD standard provides ample space
- Accommodates complex maps without crowding
- Good balance between detail and performance
- Modern displays handle this easily

**Why white color (0x00FFFFFF)?**
- High contrast against black background
- Clear visibility of all lines
- Simplifies implementation (no color gradients needed)
- Classic wireframe aesthetic

---

## 🧪 Testing

### Create Test Maps

<details>
<summary><b>Simple Test Cases</b></summary>

```bash
# Simple 3x3 peak
cat > test_maps/simple_peak.fdf << EOF
0 0 0
0 5 0
0 0 0
EOF

# Staircase pattern
cat > test_maps/stairs.fdf << EOF
0 0 0 0 0
1 1 1 1 0
2 2 2 0 0
3 3 0 0 0
4 0 0 0 0
EOF

# Valley formation
cat > test_maps/valley.fdf << EOF
5 5 5 5 5
5 3 3 3 5
5 3 0 3 5
5 3 3 3 5
5 5 5 5 5
EOF

# Flat grid (all zeros)
cat > test_maps/flat.fdf << EOF
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
EOF

# Run tests
./fdf test_maps/simple_peak.fdf
./fdf test_maps/stairs.fdf
./fdf test_maps/valley.fdf
./fdf test_maps/flat.fdf
```

</details>

### Edge Cases

| Test Case | Expected Behavior | Status |
|-----------|------------------|--------|
| **Minimum map (2x2)** | Renders 4 points with 4 lines | ✅ Works |
| **Large flat map** | Grid of white lines at base level | ✅ Works |
| **Single high peak** | Pyramid shape with visible apex | ✅ Works |
| **Negative heights** | Not handled (current version) | ⚠️ Undefined |
| **Single row** | Caught by validation (< 2x2) | ✅ Error |
| **Single column** | Caught by validation (< 2x2) | ✅ Error |
| **Empty file** | "Map Error" message | ✅ Error |
| **Non-numeric values** | Handled by ft_atoi (returns 0) | ⚠️ Silent |

---

## 📚 Resources

### MiniLibX Documentation
- [MiniLibX Guide](https://harm-smits.github.io/42docs/libs/minilibx) - Comprehensive tutorial
- [MiniLibX Man Pages](https://github.com/42Paris/minilibx-linux) - Official documentation

### Graphics Theory
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) - Integer-only line drawing
- [Isometric Projection](https://en.wikipedia.org/wiki/Isometric_projection) - 3D to 2D transformation
- [Rasterization](https://en.wikipedia.org/wiki/Rasterisation) - Converting geometry to pixels

### Useful Commands

```bash
# Check for memory leaks (macOS)
leaks -atExit -- ./fdf test_maps/42.fdf

# Check for memory leaks (Linux)
valgrind --leak-check=full ./fdf test_maps/42.fdf

# Profile performance
time ./fdf test_maps/42.fdf

# Check norminette compliance
norminette *.c *.h
```

---

## 📄 License

MIT License - See [LICENSE](LICENSE) file for details.

This project is part of the 42 School curriculum. Feel free to use and learn from this code, but please don't copy it for your own 42 projects. Understanding comes from doing it yourself! 🚀

---

## 🔗 Related Projects

Graphics programming skills learned here are used in:

- **miniRT** - Ray tracing engine with lighting and shadows
- **cub3D** - Raycasting game engine (Wolfenstein-style)
- **so_long** - 2D game with sprite rendering

---

<div align="center">

**Made with ☕ by [Z3n42](https://github.com/Z3n42)**

*42 Urduliz | Circle 2*

[![42 Profile](https://img.shields.io/badge/42_Intra-ingonzal-000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/ingonzal)

</div>
