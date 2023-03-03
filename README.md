# Riotee Arduino Core


[![Build](https://github.com/NessieCircuits/Riotee_ArduinoCore/actions/workflows/compile.yml/badge.svg)](https://github.com/NessieCircuits/Riotee_ArduinoCore/actions/workflows/compile.yml)

This repository hosts the runtime and Arduino bindings for the battery-free Riotee devices. After installation you can program the Riotee module or Riotee board conveniently from the Arduino IDE via a Riotee probe (already built into the Riotee board).

# Installation

Open the Arduino IDE and navigate to `File->Preferences`.
Open the list of board managers by clicking on the icon next to the input field for *Additional boards manager URLs*.
Add `https://nessiecircuits.github.io/Riotee_ArduinoCore/package_index.json` as one new row to the list of board manager URLs.
Confirm the changes by clicking OK.

# Usage

Select the Riotee board in the Arduino IDE under `Tools->Board->Riotee Boards->Riotee Board`.

# Releasing

The `docs/package_index.json` is automatically deployed to the repository's github page on every push to the main branch. This index file points to the zip releases that are automatically created with every tag pushed to the repository.

But there is a chicken and egg problem: `package_index.json` requires specifying size and md5 checksum of the corresponding zip release, but these are obviously only known after creating the release. Therefore, we must first create and push the tagged version and then adjust `package_index.json` in a subsequent commit after computing size and md5 checksum manually.