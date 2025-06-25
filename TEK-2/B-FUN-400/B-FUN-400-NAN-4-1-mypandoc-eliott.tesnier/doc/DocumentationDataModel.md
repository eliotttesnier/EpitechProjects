# Internal Document Data Model

This document describes the internal representation of the document data model used for the Pandoc project. The model is implemented using Abstract Data Types to represent the structure and content of all kinds of document into a single, unified structure, than can then be translated into any other suppported form, which currently include XML, JSON and Markdown

---

## Header

The `Header` type represents the metadata of a document, including its title, author, and date.

```haskell
data Header = Header String (Maybe String) (Maybe String)
```

### Fields

- **Title** (`String`): The title of the document (mandatory).
- **Author** (`Maybe String`): The author of the document (optional).
- **Date** (`Maybe String`): The date of the document (optional).

---

## Content

The `Content` type represents the various elements that can appear in the body of a document. It is a sum type with multiple constructors for different content types.

```haskell
data Content
    = PlainText String             -- Regular text
    | Bold Content                 -- Bold text
    | Italic Content               -- Italic text
    | InLineCode String            -- Inline code text
    | Link String String           -- Link (text, url)
    | Image String String          -- Image (alt text, url)
    | Paragraph [Content]          -- Paragraph of content elements
    | Section Int String [Content] -- Section with level, heading, and nested content
    | CodeBlock String             -- Code block
    | List [Item]                  -- List with items
```

### Constructors

- **PlainText** (`String`): plain text content.
- **Bold** (`Content`): bold text. The content inside the bold text is another `Content` element.
- **Italic** (`Content`): italic text. The content inside the italic text is another `Content` element.
- **Inline Code** (`String`): inline code snippets.
- **Link** (`String`, `String`): a hyperlink with the text and the URL.
- **Image** (`String`, `String`): an image with alt text and the URL.
- **Paragraph** (`[Content]`): a paragraph containing a list of `Content` elements.
- **Section** (`Int`, `String`, `[Content]`): a section with a level (e.g., heading level), a title, and nested content.
- **Code Block** (`String`): a block of code.
- **List** (`[Item]`): a list containing multiple items.

---

## Item

The `Item` type is used to represent an individual item in a list.

```haskell
data Item = Item [Content]          -- A list of `Content` elements that make up the item.
```

---

## Document

The `Document` type is used to represent the entire document, which include its header and body content.

```haskell
data Document = Document
    { docHeader :: Header           -- The header of the document.
    , docContent :: [Content]       -- A list of `Content` elements representing the body of the document.
    }
```

---

## Helper Functions

### `organizeContent`

Organizes the content of a document by grouping sections and their nested content with a "level".

```haskell
organizeContent :: [Content] -> [Content]
```

### `createStructuredDocument`

Creates a `Document` using the Header and the content.


```haskell
createStructuredDocument :: Header -> [Content] -> Document
```



