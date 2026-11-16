# Discovery report

## Problem statement

A 3D animation studio needs a ray tracer that its five developers and partner studios can understand, maintain, and extend over time, because its previous in-house tool broke with black artefacts after its creator left, but commercial licences for its 100-machine render farm cost $2 million a year and cannot be modified.

## Client interview summary

### Reliability and team continuity

**Need:** The studio needs a deterministic renderer that always gives the same output for the same input, and that any developer on the team can debug and maintain even if someone leaves.

> **Q (Stan):** "Can you share the last time your rendering tool broke?"
>
> **A:** "The last time our rendering broke was about 6 months ago on a big project. We kept finding black artefacts in the images and the rendering time doubled. Our engineering team couldn't figure out why, so we had to buy an expensive commercial licence and delivered three weeks late."

> **Q (Stan):** "What will demonstrate that the new ray tracer fits your needs?"
>
> **A:** "Two elements: first, it produces a reliable image—if I give it the same inputs, I always get the same output. Second, if there is an anomaly in an image, we can figure out why and what steps to take to fix it."

> **Q (Mathis):** "Is there any information that we need but didn't ask?"
>
> **A:** "What happens when the person who wrote it leaves the team? We had a team of five people, but the key person who wrote the software left, and nobody else knew how to debug it. We need to maintain it in the long term without you."

**My conclusion:** The studio's previous failure happened because knowledge was stuck in one person's head and there were no tests or documentation. Writing readable code, unit tests, and architecture decisions is therefore just as important as the rendering code itself.

### Cost and ownership

**Need:** Replace expensive per-machine rendering licences with an open-source C++ ray tracer owned by the studio (with a €500,000 budget and a 5 January deadline), so its internal team and partner studios can add features and fix bugs without waiting on outsiders.

> **Q (Hugo):** "What do you use today, and how much do you spend on licences?"
>
> **A:** "We render with Maya today and spend 2 million per year. Licences are paid per computer. Many machines run Maya only for rendering, and only 10 licences are actually used for 3D modelling."

> **Q (Hugo):** "Free open-source render engines already exist (Cycles, pbrt, LuxCoreRender). Why not use or extend one of them?"
>
> **A:** "With an existing open-source project, we depend on the community to fix problems, and from our experience it takes too long. We want to be the owner of the ray tracer, keep it open source, and let our partner studios contribute."

**My conclusion:** By building its own open-source ray tracer for the 100 render nodes, the studio only needs to pay for its 10 Maya modelling seats. Owning a smaller, clean C++ codebase also ensures the five-person team can fix bugs the same day instead of waiting on a vendor or an external community.

### Workflow, interface, and rendering features

**Need:** A command-line tool (with no graphical user interface) that reads a standard scene file exported from Maya and renders animated scenes—starting with spheres, planes, diffuse surfaces, reflections, and shadows—while making it easy to add new shapes and effects later.

> **Q (William Vandal):** "Do you need an interface, or can it be done without?"
>
> **A:** "No. Generally a standard file is created and saved by the designer, that file is added to the render queue, and the rendering process is launched."

> **Q (Mathis):** "What kind of films do you make, and what features do you need first?"
>
> **A:** "Mainly full animation, like Toy Story. It must render spheres and planes cleanly, with diffuse shaders, reflections, and shadows, and let us plug in our own models and features."

> **Q (William Vandal):** "What matters more: realistic images or fast images?"
>
> **A:** "The designers do not want to wait too long to see a preview, but for the final scene, high image quality is the most important thing."

**My conclusion:** We do not need to build a user interface or a Maya plugin: the ray tracer is a command-line program that takes a scene file and outputs an image. Its code must be modular so adding a new shape or shader does not require rewriting the core rendering loop.

### Performance and hardware constraints

**Need:** Render a 90-minute HD film at 24 frames per second (with around 10 iterative renders per frame during production) within two months on a farm of 100 CPU-only machines, plus quick previews on artists' desktop computers.

> **Q (Lucas):** "How long is the film, and how long can the rendering take?"
>
> **A:** "90 minutes, 24 frames per second, HD. Once the creators are done, no more than two months of rendering, on 100 CPU-only machines, with about 10 renders per image in an average workflow."

**My conclusion:** A 90-minute film at 24 FPS is 90 × 60 × 24 = 129,600 final frames, which means 1,296,000 total frame renders across 10 passes. Over 60 days on 100 machines (8,640,000 machine-minutes), each render pass can take about **6.6 minutes per machine** on average. Because the farm only has CPUs, both clean algorithms and distributed rendering across the 100 machines will be needed.

### Engineering habits and documentation

**Need:** Set up version control, coding standards, and clear developer documentation from day one.

> **Q (William Vandal):** "Do you have rules for the code, a format for documentation, or use a tool like Git?"
>
> **A:** "No specific rules for the code, and no specific format for the documentation—developers will read it. And no, we do not have a code manager like Git."

**My conclusion:** Delivering C++ code without engineering tools would repeat the studio's past problem. We need to provide a ready-to-use Git workflow, automated tests, build scripts, and short decision records (ADRs) written for developers.

### Open questions

- **Exact HD resolution:** Does HD mean 1280 × 720 (720p) or 1920 × 1080 (1080p)? 1080p has more than twice as many pixels to compute per frame.
- **File formats:** Which exact scene input format (USD, OBJ, JSON) and output image format (PNG, EXR, PPM) should we support first?
- **Hardware specs:** How many CPU cores and how much RAM does each of the 100 farm machines have, and which OS do they run?
- **Contradiction — Open source vs. no Git:** The client wants an open-source project where partner studios can contribute, yet stated they do not use a version control tool like Git. How will their team adopt Git?
- **Contradiction — Maximum realism vs. 2-month CPU deadline:** The client wants the most realistic images possible, but also requires 1.296 million renders in 60 days on 100 CPU-only machines (~6.6 minutes per pass). Do artist preview passes run at lower resolution/quality than the final pass?

## State of the art

| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| **Arnold** | Autodesk | Proprietary (subscription) | **$55/month** or **$430/year** per seat *(checked 16 Nov 2026)* | Production CPU/GPU path tracer, native Maya integration, USD support, C++ shader API | [Autodesk Arnold](https://www.autodesk.com/products/arnold/overview) |
| **RenderMan** | Pixar | Proprietary (free non-commercial tier) | **$595/licence** + **$250/year** maintenance *(checked 16 Nov 2026)* | Hybrid CPU+GPU (XPU) renderer built for animation films (*Toy Story*), native USD, Tractor farm tool | [Pixar RenderMan](https://renderman.pixar.com/store) |
| **V-Ray** | Chaos | Proprietary (subscription) | **~$540/year** (Solo) or **~$719/year** (Premium) *(checked 16 Nov 2026)* | CPU/GPU ray tracer, Maya plugin, distributed rendering across farm nodes | [Chaos V-Ray](https://www.chaos.com/vray/buy) |
| **Redshift** | Maxon | Proprietary (subscription) | **~$839/year** with Cinema 4D; standalone farm node price not published *(checked 16 Nov 2026)* | Biased GPU-first renderer with CPU fallback, fast artist previews, Maya plugin | [Maxon Redshift](https://www.maxon.net/en/redshift) |
| **Cycles** | Blender Foundation | Open Source (Apache-2.0) | **Free** ($0) *(checked 16 Nov 2026)* | CPU/GPU path tracer, standalone CLI mode, USD and OSL shader support | [Cycles Renderer](https://www.cycles-renderer.org/) |
| **MoonRay** | DreamWorks | Open Source (Apache-2.0) | **Free** ($0) *(checked 16 Nov 2026)* | C++ production ray tracer built for feature animation, multi-machine Arras rendering | [OpenMoonRay](https://openmoonray.org/) |
| **PBRT (v4)** | Pharr, Jakob, Humphreys | Open Source (Apache-2.0) | **Free** ($0) *(checked 16 Nov 2026)* | Clean C++17 physically based ray tracer designed for learning and research | [pbrt.org](https://pbrt.org/) |

**Conclusion:** Commercial renderers like Arnold, RenderMan, and V-Ray work great with Maya, but they are closed-source black boxes and cost too much across a 100-machine farm. Open-source engines like Cycles and MoonRay are free, but their codebases contain hundreds of thousands of lines, making it hard for a five-person team to understand everything and fix bugs quickly without relying on an external community. Building a focused, well-tested C++ ray tracer gives the studio full ownership and control.

## What is ray tracing?

Ray tracing is a rendering technique that generates a 2D image from a 3D scene by simulating the path of light. As **input**, it reads a 3D scene description containing a camera, 3D objects (such as spheres and planes), surface materials, and light sources. As **output**, it produces a 2D grid of coloured pixels saved as an image file. **In between**, instead of sending rays from the light sources (since most rays would miss the camera), it works **backwards from the eye**: for every pixel of the image, it shoots a ray from the camera into the scene and checks which object it intersects first. At that hit point, it calculates the surface normal and sends secondary rays—**shadow rays** toward the lights to see if the point is in shadow, and **reflection rays** that bounce off shiny surfaces—to compute the final colour of the pixel.

**Sources:**
- **To get started:** [*Ray Tracing in One Weekend*](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley — chosen because it explains ray tracing step by step from basic vectors to spheres, camera rays, and materials in simple C++.
- **Reference:** [*Physically Based Rendering (4th ed.)*](https://pbr-book.org/4ed/contents) by Matt Pharr, Wenzel Jakob, and Greg Humphreys — chosen because it is the complete reference book used across the industry for ray tracing maths and C++ design.

## What is C++?

### Programming paradigms

C++ is a statically typed, compiled language that supports procedural, object-oriented, generic (templates), and functional programming. Compared to **C#**, which I already know, both languages use classes, interfaces, and strong typing, but C++ compiles directly to native machine code without a virtual machine or runtime like .NET's CLR. C++ also splits code into header files (`.h`, which declare what a class does) and implementation files (`.cpp`, which contain the logic), allows free functions outside classes, and resolves templates at compile time for better performance.

### What to watch out for

Coming from **C#**, where the .NET runtime handles garbage collection and safety checks automatically, C++ leaves several traps to watch out for:

- **Memory and ownership:** There is no Garbage Collector in C++. To avoid memory leaks or dangling pointers, we should avoid raw `new`/`delete` and use stack variables or smart pointers like `std::unique_ptr`, so every object has a clear owner.
- **Pass by value vs. reference:** In C#, class objects are passed by reference automatically. In C++, objects are copied by value by default. We must use `const T&` (like `const Vector&`) to avoid slow copies, and never pass polymorphic objects by value to avoid *object slicing*.
- **Undefined behaviour:** In C#, reading outside an array or using `null` throws a clean exception. In C++, reading an uninitialised variable or going out of bounds causes undefined behaviour: the program can crash or silently produce wrong pixels.
- **Number and conversion traps:** `double` values cannot be compared with `==` because of binary rounding (we must use a small tolerance), dividing two `int` values drops the decimal part (`5 / 2 == 2`), and single-argument constructors should use `explicit` to prevent accidental type conversions.

### Shaping the domain model

These C++ features directly shape how we should build our ray tracer's domain model:

1. **Small immutable value types:** Math objects like `Vector`, `Colour`, `Ray`, and `Hit` are used millions of times per image. We should write them as small stack-allocated classes (similar to `readonly struct` in C#) with `const` methods and operator overloads (`O + t * D`) so the code reads like the maths.
2. **Interfaces and polymorphism for extensibility:** To add new shapes or image formats without modifying existing code (Open/Closed Principle), we should use pure virtual interface classes like `Shape` and `ImageSaver`. High-level code (`Scene`, `Camera`) only depends on the `Shape` header, while `Sphere` and `Plane` keep their intersection maths in their own `.cpp` files.
3. **Explicit ownership and optional values:** A `Scene` should own its shapes using `std::vector<std::unique_ptr<Shape>>` (moving them in with `std::move`), and intersection checks should return `std::optional<Hit>` instead of `null` or `-1`, forcing the caller to check whether a ray actually hit something.

**Sources:**
- **To get started:** [*LearnCpp.com*](https://www.learncpp.com/) — chosen because it teaches modern C++ step by step (headers, `const&`, classes, and smart pointers) in plain English.
- **Reference:** [*cppreference.com*](https://en.cppreference.com/w/cpp) and the [*C++ Core Guidelines*](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) — chosen as the reference to check standard library types (`std::optional`, `std::unique_ptr`) and C++ best practices.
