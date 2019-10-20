# Contributing
## Features in-progress

#### Development

This feature modules are stored in `nyann/drafts` folder at have names formated as follows:

```
<feature module/class>_draft
```

This features will be added after tests and reconsideration.

#### System preparation

Blocks of code for system preparation for merging with draft-features are separated with:

```c+
#ifdef DRAFT_<feature name>
...
#endif
```

## Glossary

**feature** - class or module