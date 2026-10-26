# Board Game Database & Search Application (Java 21 / JavaFX / XML / MVC)

**Course:** CS 321 — Intro to Object-Oriented Programming in Java (University of Alabama in Huntsville)  
**Author & Key Contributor:** Emma Planson (`@plansonec`) — *XML DOM Parsers, Session & Theme State Architecture, High-Contrast Accessibility Mode, and JavaFX UI Views*  
**Tech Stack:** Java 21, JavaFX 21 (FXML & CSS), DOM XML Parsing (`javax.xml.parsers` & `javax.xml.transform`), Gradle, MVC + Singleton Design Patterns

## Executive Overview

The **Board Game Database & Search Application** is a desktop application architected around the **Model-View-Controller (MVC)** and **Singleton** design patterns to parse, catalog, filter, and manage a 90-game dataset exported from BoardGameGeek (`bgg90Games.xml`). Users can authenticate, search and filter board games by title, player count, and playing time, inspect detailed game descriptions and community reviews, build custom persisted XML wishlists, and toggle a full **WCAG-oriented High-Contrast Accessibility Theme** with adjustable typography scaling across all views.

## Architectural Structure & Key Contributions

The project separates data persistence, domain logic, and user interface presentation into distinct packages under `src/main/java/org/example/`:

| Component / File | Layer | Architectural Responsibility |
| :--- | :--- | :--- |
| `model/GameParser.java` | Model (Data Access) | Parses `bgg90Games.xml` via Java's DOM `DocumentBuilder`, normalizing XML nodes, extracting attributes (`id`, `name`, `minplayers`, `maxplayers`, `playingtime`, `image`, `description`), and caching the master `List<Game>` in memory. |
| `model/UserParser.java` | Model (Data Access) | Parses `sampleUser.xml` and `userWishlists.xml` to reconstruct `User` accounts and associated `Wishlist` collections. |
| `model/Session.java` | Model (State Singleton) | Manages global session state (`currentUser`, `currentGame`, `currentWishlists`), persists updated wishlists back to XML via `Transformer`, and applies global UI accessibility preferences (`highContrast` and `textSize`) across JavaFX scenes. |
| `model/Game.java` & `Review.java` | Model (Domain) | Encapsulates board game metadata, player bounds, playtime, cover art URLs, and immutable review lists (`getReviews()` returns an unmodifiable view to preserve encapsulation). |
| `model/Wishlist.java` | Model (Domain) | Represents named user game collections with duplicate-safe addition, removal, and lookup operations. |
| `model/GameSearch.java` & `UserSearch.java` | Model (Query Engine) | Provides multi-criteria filtering and keyword search across cached game records and user profiles. |
| `views/MainView.java` & `mainView.fxml` | View / Controller | Implements the primary catalog grid, asynchronous cover-art loading, multi-filter search bar, accessible navigation banner, and keyboard-friendly wishlist creation dialogs. |
| `views/GameView.java` & `gameView.fxml` | View / Controller | Renders individual game specifications, formatted descriptions, dynamic window scaling, and user review submission panels. |
| `views/WishlistView.java` & `wishlistView.fxml` | View / Controller | Displays user wishlists, game cards, and favorite toggles with full high-contrast support. |
| `views/LoginView.java` & `SettingsViewController.java` | View / Controller | Handles user authentication, screen-reader accessible form labels, and global accessibility toggles (High-Contrast Mode & dynamic font sizing). |
| `resources/org.openjfx/highContrast.css` | Accessibility UI | Implements an industry-standard `#000000` (black) surface palette with `#FFFF00` (high-visibility yellow) typography, `#00FFFF` (cyan) links, and `2px` `#FFFFFF` focus/element borders, removing drop-shadow blur for maximum legibility. |

## Accessibility Engineering Highlights

1. **Global High-Contrast Theme Engine (`Session.applyGlobalSettings` + `highContrast.css`)**:
   - Replaces low-contrast gradients and drop shadows with crisp `2px` solid white borders on a pure black (`#000000`) canvas and high-luminance yellow (`#FFFF00`) interactive states.
   - Persists theme and text-size preferences across scene transitions (`LoginView`, `MainView`, `GameView`, `WishlistView`, and `SettingsView`).
2. **Accessible Navigation & Form Controls**:
   - Replaced native OS menu bars with an explicit, keyboard-focusable `.menu-banner` toolbar.
   - Added explicit accessible labels and focus indicators to login inputs, favorite toggle buttons, and wishlist creation dialogs.

## Unit Test Suite (`src/test/java/`)

The repository includes 8 automated tester classes validating XML parsing, domain encapsulation, and search accuracy:
- `GameParserTester.java` — Verifies DOM parsing of `bgg90Games.xml` and attribute extraction.
- `GameSearchTester.java` — Tests keyword, player-count, and play-time filtering.
- `GameTester.java` — Validates `Game` and `Review` constructors, getters, and immutable collection returns.
- `UserParserTester.java` & `UserParsingSearchTester.java` — Verifies XML user deserialization and lookup.
- `UserSearchTester.java` & `UserTester.java` — Tests user account management and credential checks.
- `WishListTester.java` — Confirms wishlist item insertion, removal, and duplicate prevention.

## How to Build and Run

### Prerequisites
- **Java Development Kit (JDK):** Version 21 or higher
- **Build System:** Gradle (included via `./gradlew` wrapper)

### Run the Desktop Application
```bash
./gradlew run
```

### Compile Classes & Run Tests
```bash
./gradlew compileJava compileTestJava
```
