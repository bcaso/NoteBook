# Welcome to MkDocs

**For full documentation visit** [mkdocs.org](https://www.mkdocs.org).
<br/>


# Tutorial
mkdocs download and install configuration: [https://www.cnblogs.com/fzxiaomange/p/mkdocs-material.html](https://www.cnblogs.com/fzxiaomange/p/mkdocs-material.html)

>theme: **mkdocs-material** usage: 
[https://cyent.github.io/markdown-with-mkdocs-material/](https://cyent.github.io/markdown-with-mkdocs-material/)
[https://squidfunk.github.io/mkdocs-material/](https://squidfunk.github.io/mkdocs-material/)

## Commands

* `mkdocs new [dir-name]` - Create a new project.
* `mkdocs serve` - Start the live-reloading docs server.
* `mkdocs build` - Build the documentation site.
* `mkdocs -h` - Print help message and exit.

Deploying your docs: [https://www.mkdocs.org/user-guide/deploying-your-docs/](https://www.mkdocs.org/user-guide/deploying-your-docs/)

Here's how to submit changes after deployment:

<br>
!!! note
    Under the **master** branch, 

    1. Change your file and `commit`,Make sure you can see the effect on [https://localhost:8000](https://localhost:8000)

    2. run `git push`, press the update of the local branch to the remote host.

    3. At last `mkdocs gh-deploy`, deploy your site on GitPages.



## Project layout

    mkdocs.yml    # The configuration file.
    docs/
        index.md  # The documentation homepage.
        ...       # Other markdown pages, images and other files.
<br/>

!!! note
    There can be no other files in the same level directory of mkdocs.yml, including README.MD, but temporary files of vim are fine

