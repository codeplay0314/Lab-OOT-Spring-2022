# Design Patterns Used in this Lab

Here's 4 main design patterns used in this Lab:

## Composite
**Composite** is used to build the `Command` abstract class, and its subclasses `LineCommand`, `TextCommand` and `ColorCommand`, `MacroCommand`, where `MacroCommand` includes a vector containing multiple `Command`s.
<br />

```plantuml
@startuml
package command.h {
    class Command
    class LineCommand
    class TextCommand
    class ColorCommand
    class MacroCommand
}
abstract class Command {
    Execute()
    Undo()
    Redo()
}

class LineCommand extends Command {
    Execute()
}

class TextCommand extends Command {
    Execute()
}

class ColorCommand extends Command {
    Execute()
}

class MacroCommand extends Command {
    commands : vector<Command>
    Execute()
    Undo()
    Redo()
}

MacroCommand "commands" o--* Command

note left of MacroCommand::Execute()
    for (command : commands) {
        command->Execute();
    }
endnote
note left of MacroCommand::Undo()
    for (command : commands) {
        command->Undo();
    }
endnote
note left of MacroCommand::Redo()
    for (command : commands) {
        command->Redo();
    }
endnote

@enduml
```
<br />
<br />
<br />
<br />

## Command
**Command** is used to organize how the commands are invoked to apply to its receicer by the client. It also facilitates the Undo() and Redo() methods.

```plantuml
@startuml
package command.h {
    class Command
    class LineCommand
    class TextCommand
    class ColorCommand
    class MacroCommand
}
abstract class Command {
    board : Board
    Execute()
    Undo()
    Redo()
}

class LineCommand extends Command {
    Execute()
}

class TextCommand extends Command {
    Execute()
}

class ColorCommand extends Command {
    Execute()
}

class MacroCommand extends Command {
    commands : vector<Command>
    Execute()
}
MacroCommand "commands" o--* Command

package cmd_invoker.h {
    class CommandInvoker
}

class CommandInvoker {
    Execute()
}
CommandInvoker  o--* Command

package board.h {
    class Board
}
Board  "receiver" --* Command

package draw.h {
    class Client
}
class Client
Client --* Board
Client ..> MacroCommand
Client ..> TextCommand
Client ..> LineCommand
Client ..> ColorCommand

@enduml
```

<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />

## State
**State** is used to help `Board` to switch between two gray scale modes according to the command line parameters, [-g 2] or [-g 256].
```plantuml
@startuml
package gray_scale.h {
    class GrayScale
    class BW2Scale
    class BW256Scale
}
abstract class GrayScale {
    GetColor()
}

class BW2Scale extends GrayScale {
    GetColor()
}

class BW256Scale extends GrayScale {
    GetColor()
}

package board.h {
    class Board
}
class Board {
    gscale : GrayScale
    GetColor()
}
Board "gscale" o--* GrayScale

note right of Board::GetColor()
    gscale->GetColor()
endnote

@enduml
```

## Singleton
**Singleton** is used because gray scale modes only need one instance each.

```plantuml
@startuml
package gray_scale.h {
    class BW2Scale
    class BW256Scale
}

class BW2Scale {
    {static} Instance() : GrayScale
    {static} _instance : GrayScale
}
note right of BW2Scale::Instance()
    return _instance
endnote

class BW256Scale {
    {static} Instance() : GrayScale
    {static} _instance : GrayScale
}
@enduml
```
