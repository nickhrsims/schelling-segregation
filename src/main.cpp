#include <cstdint>
#include <cstdlib>

#include <stdexcept>
#include <vector>

#include <sos/sos.h>

#include "grid.h"

// -----------------------------------------------------------------------------
// Types
// -----------------------------------------------------------------------------

enum class cell {
    vacant,
    red,
    blue,
};

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------

int main() {

    sos::root::init({.headless = false,
                     .window   = {
                           .title = "Schelling",
                           .x     = 64,
                           .y     = 64,
                           .w     = 50 * 8,
                           .h     = 50 * 8,
                     }});

    // ---------------------------------
    // Initialize Cell Table
    // ---------------------------------
    grid<cell> cells{50, cell::vacant};

    // --- Set random distribution to red.
    for (int count = 0; count < (50 * 50) / 4; ++count) {
        cells.set(cells.find_random(cell::vacant), cell::red);
    }

    // --- Set random distribution to blue.
    for (int count = 0; count < (50 * 50) / 4; ++count) {
        cells.set(cells.find_random(cell::vacant), cell::blue);
    }

    float target_homogeny = 1.f / 3.f;

    // ---------------------------------
    // Loop until stop
    // ---------------------------------

    sos::process::start([&cells, &target_homogeny](float) {
        //
        // --- Update
        //

        for (auto row = 0; row < cells.size(); ++row) {
            for (auto col = 0; col < cells.size(); ++col) {

                grid<cell>::position self{row, col};

                if (cells.get(self) != cell::vacant) {

                    int homogeneous_neighbors = 0;

                    for (auto& neighbor : cells.neighbors(self)) {
                        if (neighbor != cell::vacant && neighbor == cells.get(self)) {
                            ++homogeneous_neighbors;
                        }
                    }

                    float actual_homogeny =
                        static_cast<float>(homogeneous_neighbors) /
                        static_cast<float>(cells.neighbors(self).size());

                    if (actual_homogeny < target_homogeny) {
                        cells.swap(cells.find_random(cell::vacant), self);
                    }
                }
            }
        }

        //
        // --- Render
        //

        constexpr sos::video::color black{0, 0, 0, 255};
        constexpr sos::video::color white{255, 255, 255, 255};
        constexpr sos::video::color red{255, 0, 0, 255};
        constexpr sos::video::color blue{0, 0, 255, 255};

        sos::video::renderer::set_color(black);
        sos::video::renderer::clear();

        for (auto row = 0; row < cells.size(); ++row) {
            for (auto col = 0; col < cells.size(); ++col) {
                grid<cell>::position self{row, col};
                switch (cells.get(self)) {
                case cell::red:
                    sos::video::renderer::set_color(red);
                    break;
                case cell::blue:
                    sos::video::renderer::set_color(blue);
                    break;
                case cell::vacant:
                    sos::video::renderer::set_color(white);
                    break;
                }
                sos::rect location{col * 8, row * 8, 8, 8};
                sos::video::renderer::draw(location);
            }
        }

        sos::video::renderer::show();
    });

    sos::root::quit();
    return EXIT_SUCCESS;
}
