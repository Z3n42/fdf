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

- ✅ Reads and parses `.fdf` map files
- ✅ Isometric projection rendering (angle: 0.7 radians ≈ 40°)
- ✅ Bresenham's line drawing algorithm
- ✅ Handles maps of any size
- ✅ Altitude-based scaling (z * 5)
- ✅ Resolution: 1920x1080
- ✅ Simple ESC key to exit

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

After running `make`, you'll have an `fdf` executable ready to use.

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

| Key | Action |
|-----|--------|
| **ESC** (key 53) | Close window and exit program |

---

## 📄 Map Format

Maps are stored in `.fdf` files with a simple grid format:

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
- **Horizontal position** = X coordinate (column)
- **Vertical position** = Y coordinate (row)
- Minimum map size: **2x2**
- Maximum: limited by memory

### Error Handling

The program validates:
- File existence
- Minimum map dimensions (2x2)
- Valid format (numbers separated by spaces)

Error message: `Map Error` followed by exit.

---

## 🎨 How It Works

### From Map to Wireframe

Let's visualize how a simple pyramid transforms into a 3D wireframe:

#### Step 1: Input Map
```
Map file (pyramid.fdf):
0  0  0  0  0
0  1  1  1  0
0  1  2  1  0
0  1  1  1  0
0  0  0  0  0

Grid:        Heights:
  0 1 2 3 4    0 0 0 0 0
0 • • • • •    0 1 1 1 0
1 • • • • •    0 1 2 1 0
2 • • • • •    0 1 1 1 0
3 • • • • •    0 0 0 0 0
4 • • • • •
```

#### Step 2: 3D Space Interpretation
```
Each point (x, y) has a height z:
Point (2, 2) = height 2 (peak)
Point (1, 2) = height 1
Point (0, 0) = height 0 (ground)

Side View (looking from X axis):
    2   •              ← Peak
    1   • • •          ← Mid level  
    0   • • • • •      ← Ground
        ─────────
        0 1 2 3 4
```

#### Step 3: Isometric Projection
```
Formula used in the code:
xb = (x - y) * cos(0.7) + 600
yb = (y + x) * sin(0.7) - 450 - z * 5

Result (ASCII approximation):
       •           ← (2,2,2) Peak
      /│\
     • • •         ← Height 1 ring
    /│ │ │\
   • • • • •       ← Ground level

Legend:
• = Vertex (point)
│ = Vertical line
/ \ = Diagonal lines
```

### Algorithm Flow

```
1. Parse Map
   ├─ ft_xcount()  → Count columns
   ├─ ft_open()    → Validate dimensions
   └─ ft_matrix()  → Create 2D int array

2. Initialize Graphics
   ├─ mlx_init()   → Start MiniLibX
   ├─ mlx_new_window(1920, 1080)
   └─ mlx_new_image()

3. Draw Wireframe
   ├─ ft_draw_x()  → Connect horizontal lines
   │  └─ For each row, connect adjacent points
   │
   ├─ ft_draw_y()  → Connect vertical lines
   │  └─ For each column, connect adjacent points
   │
   └─ ft_brasenham() → Draw each line segment

4. Display & Wait
   ├─ mlx_put_image_to_window()
   ├─ mlx_key_hook()  → Listen for ESC
   └─ mlx_loop()      → Event loop
```

---

## 📁 Project Structure

```
fdf/
├── 📄 Makefile              # Build configuration
├── 📄 fdf.h                 # Header with structs and prototypes
├── 📄 LICENSE               # MIT License
├── 📄 fdf.c                 # Main: parsing and initialization
├── 📄 draw2.c               # Drawing functions (ft_draw_x, ft_draw_y)
├── 📄 drw_aux.c             # Bresenham algorithm & utilities
├── 📂 libft/                # Custom C library
│   └── libft.h, ft_*.c
├── 📂 mlx/                  # MiniLibX graphics library
│   └── mlx.h, libmlx.a
└── 📂 test_maps/            # Example .fdf map files
```

### File Descriptions

| File | Lines | Purpose |
|------|-------|---------|
| `fdf.c` | ~90 | Entry point, map parsing, matrix creation |
| `draw2.c` | ~110 | Main rendering: `ft_draw()`, `ft_draw_x()`, `ft_draw_y()` |
| `drw_aux.c` | ~80 | Bresenham implementation: `ft_plotlow()`, `ft_plothigh()` |
| `fdf.h` | ~50 | Structs (`t_data`, `t_cord`, `t_a`) and function prototypes |

### Data Structures

#### t_data - MiniLibX Context
```c
typedef struct s_data {
    void        *mlx;      // MLX instance
    void        *mlx_win;  // Window pointer
    void        *img;      // Image pointer
    char        *addr;     // Image data address
    int         bits;      // Bits per pixel
    int         line;      // Line size in bytes
    int         end;       // Endianness
    uintptr_t   col;       // Color
} t_data;
```

#### t_cord - Coordinate System
```c
typedef struct s_cord {
    int x, x1;      // Original X coordinates
    int y, y1;      // Original Y coordinates
    int xb, xb1;    // Transformed screen X
    int yb, yb1;    // Transformed screen Y
    int z, z1;      // Z height values
    int dx, dy;     // Bresenham deltas
    int p;          // Bresenham decision parameter
    int xi, yi;     // Bresenham increments
    int av, ve;     // Loop counters
} t_cord;
```

#### t_a - Map Data
```c
typedef struct s_a {
    int     x;      // Map width (columns)
    int     y;      // Map height (rows)
    int     fd;     // File descriptor
    char    *tab;   // Temporary line buffer
    int     **m;    // 2D matrix of heights
} t_a;
```

---

## 🔧 Technical Details

### Isometric Projection

Implementation uses a **custom angle of 0.7 radians** (≈40°) instead of the standard 30°:

```c
// In ft_draw_x() and ft_draw_y()
xb = (x - y) * cos(0.7) + 600;      // Horizontal position
yb = (y + x) * sin(0.7) - 450 - z * 5;  // Vertical with altitude
```

**Parameters:**
- `cos(0.7)` ≈ 0.765 (horizontal compression)
- `sin(0.7)` ≈ 0.644 (vertical compression)
- Offset: (600, -450) centers the image
- Z scaling: `z * 5` amplifies height differences

### Bresenham's Algorithm

Implementation in `drw_aux.c`:

#### Plotlow - Shallow Lines (|slope| < 1)
```c
void ft_plotlow(t_data *img, t_cord *c)
{
    dx = xb1 - xb;
    dy = yb1 - yb;
    yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    p = 2 * (dy - dx);
    while (xb++ < xb1) {
        if (xb < 1919 && yb < 1079 && xb > 0 && yb > 0)
            my_mlx_pixel_put(img, xb, yb, 0x00FFFFFF);  // White
        if (p > 0) {
            yb += yi;
            p += 2 * (dy - dx);
        } else {
            p += 2 * dy;
        }
    }
}
```

#### Plothigh - Steep Lines (|slope| ≥ 1)
```c
void ft_plothigh(t_data *img, t_cord *c)
{
    // Similar logic but iterates over Y axis
    // Ensures smooth lines regardless of slope
}
```

### Map Parsing

#### 1. Count Columns (`ft_xcount`)
```c
int ft_xcount(char const *s, char c)
{
    int counter = 0;
    int pos = 0;
    while (s[counter]) {
        if (s[counter] == c && s[counter + 1] != c)
            pos++;
        counter++;
    }
    return (s[counter - 1] == ' ') ? pos : pos + 1;
}
```

#### 2. Create Matrix (`ft_matrix`)
```c
int **ft_matrix(int fd, int x, int y)
{
    int **mat = (int **)malloc(y * sizeof(int *));
    int j = 0;

    while (get_next_line(fd, &str)) {
        tbl = ft_split(str, ' ');
        mat[j] = (int *)malloc(x * sizeof(int));
        for (int i = 0; tbl[i]; i++)
            mat[j][i] = ft_atoi(tbl[i]);
        j++;
    }
    return mat;
}
```

### Drawing Strategy

#### Connect Horizontal Lines (`ft_draw_x`)
```c
// For each row:
// - Start at initial position
// - Connect point[i] to point[i+1]
// - Apply isometric transformation
// - Draw line with Bresenham
```

#### Connect Vertical Lines (`ft_draw_y`)
```c
// For each column:
// - Start at initial position  
// - Connect point[j] to point[j+1]
// - Apply isometric transformation
// - Draw line with Bresenham
```

---

## 💡 What I Learned

Through this project, I gained deep understanding of:

- ✅ **Computer Graphics Fundamentals**: Rasterization, projection formulas
- ✅ **MiniLibX Library**: Window creation, image manipulation, pixel buffer
- ✅ **Bresenham's Algorithm**: Integer-only line drawing for efficiency
- ✅ **Isometric Projection**: Converting 3D coordinates to 2D display
- ✅ **File Parsing**: Reading structured text files with `get_next_line`
- ✅ **2D Array Management**: Dynamic allocation and proper memory freeing
- ✅ **Linear Algebra**: Trigonometric transformations (cos/sin)
- ✅ **Memory Management**: Handling complex nested structures
- ✅ **Event Handling**: Keyboard hooks with MiniLibX

### Key Challenges

1. **Understanding Isometric Math**: Converting 3D world space to 2D screen space using trigonometry
2. **Bresenham Implementation**: Handling both shallow and steep lines without float arithmetic
3. **Map Parsing**: Counting columns accurately and creating dynamic 2D arrays
4. **Coordinate Systems**: Managing multiple coordinate spaces (map, world, screen)
5. **Memory Leaks**: Properly freeing 2D arrays and MLX resources
6. **Screen Clipping**: Preventing drawing outside window bounds (0-1919, 0-1079)

### Design Decisions

**Why 0.7 radians?**
- Standard isometric: 30° (0.523 rad)
- My choice: 40° (0.7 rad)
- Result: Slightly more "top-down" view

**Why z * 5?**
- Amplifies altitude differences
- Makes height variations more visible
- Small z values would be barely noticeable

**Why 1920x1080?**
- Full HD resolution
- Provides ample space for complex maps
- Good balance between detail and performance

---

## 🧪 Testing

### Create Test Maps

```bash
# Simple 3x3 peak
cat > test_maps/simple_peak.fdf << EOF
0 0 0
0 5 0
0 0 0
EOF

# Staircase
cat > test_maps/stairs.fdf << EOF
0 0 0 0 0
1 1 1 1 0
2 2 2 0 0
3 3 0 0 0
4 0 0 0 0
EOF

# Valley
cat > test_maps/valley.fdf << EOF
5 5 5 5 5
5 3 3 3 5
5 3 0 3 5
5 3 3 3 5
5 5 5 5 5
EOF

./fdf test_maps/simple_peak.fdf
```

### Edge Cases

- **Minimum map (2x2)**: Should render 4 points with 4 lines
- **Large flat map**: All zeros, should render grid
- **Negative heights**: Not handled in current version
- **Single row/column**: Caught by validation (< 2x2)

---

## 📚 Resources

### MiniLibX Documentation
- [MiniLibX Guide](https://harm-smits.github.io/42docs/libs/minilibx)
- [MiniLibX Man Pages](https://github.com/42Paris/minilibx-linux)

### Graphics Theory
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Isometric Projection](https://en.wikipedia.org/wiki/Isometric_projection)
- [Rasterization](https://en.wikipedia.org/wiki/Rasterisation)

### Useful Commands

```bash
# Check for memory leaks (macOS)
leaks -atExit -- ./fdf test_maps/42.fdf

# Check for memory leaks (Linux)
valgrind --leak-check=full ./fdf test_maps/42.fdf

# Profile performance
time ./fdf test_maps/42.fdf
```

---

## 📄 License

MIT License - See [LICENSE](LICENSE) file for details.

This project is part of the 42 School curriculum. Feel free to use and learn from this code, but please don't copy it for your own 42 projects. Understanding comes from doing it yourself! 🚀

---

## 🔗 Related Projects

Graphics programming skills learned here are used in:

- **miniRT** - Ray tracing engine
- **cub3D** - Raycasting game (Wolfenstein-style)
- **so_long** - 2D game with sprites

---

<div align="center">

**Made with ☕ by [Z3n42](https://github.com/Z3n42)**

*42 Urduliz | Circle 2*

[![42 Profile](https://img.shields.io/badge/42_Intra-ingonzal-000000?style=flat&logo=42&logoColor=white)](https://profile.intra.42.fr/users/ingonzal)

</div>
