<!DOCTYPE html>
<html lang="my">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<title>velvet gemsNotes</title>

<style>
*{
    box-sizing:border-box;
    font-family:Arial,sans-serif;
}

body{
    margin:0;
    background:#f7f7f7;
    color:#222;
}

header{
    background:#d71920;
    color:white;
    text-align:center;
    padding:25px 15px;
}

header h1{
    margin:0;
    font-size:26px;
}

header p{
    margin:8px 0 0;
}

.container{
    max-width:900px;
    margin:20px auto;
    padding:0 15px;
}

.card{
    background:white;
    padding:20px;
    margin-bottom:20px;
    border-radius:15px;
    box-shadow:0 3px 12px rgba(0,0,0,.08);
}

h2{
    color:#d71920;
    margin-top:0;
}

input,textarea{
    width:100%;
    padding:13px;
    margin:7px 0 14px;
    border:1px solid #ddd;
    border-radius:9px;
    font-size:15px;
}

textarea{
    height:110px;
    resize:vertical;
}

button{
    border:0;
    border-radius:9px;
    padding:12px 18px;
    cursor:pointer;
    font-size:15px;
}

.save{
    width:100%;
    background:#d71920;
    color:white;
}

.save:hover{
    background:#b51218;
}

.search{
    border:2px solid #d71920;
}

.design{
    border-left:5px solid #d71920;
    background:white;
    padding:16px;
    margin-top:15px;
    border-radius:10px;
    box-shadow:0 2px 8px rgba(0,0,0,.06);
}

.design h3{
    color:#d71920;
    margin-top:0;
}

.design img{
    width:100%;
    max-height:300px;
    object-fit:contain;
    border-radius:10px;
    margin:10px 0;
}

.date{
    color:#888;
    font-size:13px;
    margin-bottom:10px;
}

.edit{
    background:#333;
    color:white;
    margin-right:5px;
}

.delete{
    background:#d71920;
    color:white;
}

.empty{
    text-align:center;
    color:#999;
    padding:25px;
}
</style>
</head>

<body>

<header>
    <h1>💎 Jewelry Design</h1>
    <p>My Design Notes</p>
</header>

<div class="container">

<!-- ADD DESIGN -->
<div class="card">

<h2>➕ Design အသစ်ထည့်ရန်</h2>

<input id="name"
       type="text"
       placeholder="Design Name">

<input id="gold"
       type="text"
       placeholder="Gold Weight">

<input id="stone"
       type="text"
       placeholder="Stone / Gem">

<textarea id="note"
          placeholder="Design အကြောင်းအရာ၊ အတိုင်းအတာ၊ မှတ်ချက်..."></textarea>

<input id="image"
       type="file"
       accept="image/*">

<button class="save"
        onclick="saveDesign()">

💾 Design သိမ်းမယ်

</button>

</div>


<!-- SEARCH -->
<div class="card">

<h2>🔎 Design ရှာရန်</h2>

<input class="search"
       id="search"
       type="text"
       placeholder="Design Name ရိုက်ရှာပါ..."
       oninput="showDesigns()">

</div>


<!-- DESIGN LIST -->
<div class="card">

<h2>💎 My Designs</h2>

<div id="designList"></div>

</div>

</div>


<script>

let designs =
JSON.parse(localStorage.getItem("jewelryDesigns")) || [];

let editIndex = -1;


// SAVE DESIGN
function saveDesign(){

    let name =
    document.getElementById("name").value.trim();

    let gold =
    document.getElementById("gold").value.trim();

    let stone =
    document.getElementById("stone").value.trim();

    let note =
    document.getElementById("note").value.trim();

    let file =
    document.getElementById("image").files[0];


    if(name === ""){

        alert("Design Name ထည့်ပေးပါ");

        return;
    }


    if(file){

        let reader = new FileReader();

        reader.onload = function(e){

            saveData(
                name,
                gold,
                stone,
                note,
                e.target.result
            );

        };

        reader.readAsDataURL(file);

    }else{

        saveData(
            name,
            gold,
            stone,
            note,
            ""
        );

    }

}


// SAVE DATA
function saveData(
    name,
    gold,
    stone,
    note,
    image
){

    let design = {

        name:name,

        gold:gold,

        stone:stone,

        note:note,

        image:image,

        date:new Date().toLocaleDateString()

    };


    if(editIndex === -1){

        designs.push(design);

    }else{

        designs[editIndex] = design;

        editIndex = -1;

    }


    localStorage.setItem(
        "jewelryDesigns",
        JSON.stringify(designs)
    );


    clearForm();

    showDesigns();

    alert("Design သိမ်းပြီးပါပြီ ✅");

}


// SHOW DESIGNS
function showDesigns(){

    let list =
    document.getElementById("designList");

    let search =
    document.getElementById("search")
    .value
    .toLowerCase();


    list.innerHTML = "";


    let filtered =
    designs.filter(function(d){

        return d.name
        .toLowerCase()
        .includes(search);

    });


    if(filtered.length === 0){

        list.innerHTML =
        `<div class="empty">
        💎 Design မရှိသေးပါ
        </div>`;

        return;

    }


    filtered.forEach(function(d){

        let index =
        designs.indexOf(d);


        list.innerHTML += `

        <div class="design">

            <h3>
            💎 ${escapeHTML(d.name)}
            </h3>

            <div class="date">
            📅 ${d.date}
            </div>

            ${
                d.image
                ?
                `<img src="${d.image}">`
                :
                ""
            }

            <p>
            <b>Gold:</b>
            ${escapeHTML(d.gold || "-")}
            </p>

            <p>
            <b>Stone:</b>
            ${escapeHTML(d.stone || "-")}
            </p>

            <p>
            <b>Note:</b><br>
            ${escapeHTML(d.note || "-")}
            </p>


            <button
            class="edit"
            onclick="editDesign(${index})">

            ✏️ Edit

            </button>


            <button
            class="delete"
            onclick="deleteDesign(${index})">

            🗑️ Delete

            </button>

        </div>

        `;

    });

}


// EDIT
function editDesign(index){

    let d = designs[index];


    document.getElementById("name")
    .value = d.name;


    document.getElementById("gold")
    .value = d.gold;


    document.getElementById("stone")
    .value = d.stone;


    document.getElementById("note")
    .value = d.note;


    editIndex = index;


    window.scrollTo({

        top:0,

        behavior:"smooth"

    });

}


// DELETE
function deleteDesign(index){

    if(
        confirm(
        "ဒီ Design ကို ဖျက်မှာသေချာလား?"
        )
    ){

        designs.splice(index,1);


        localStorage.setItem(
            "jewelryDesigns",
            JSON.stringify(designs)
        );


        showDesigns();

    }

}


// CLEAR
function clearForm(){

    document.getElementById("name")
    .value = "";

    document.getElementById("gold")
    .value = "";

    document.getElementById("stone")
    .value = "";

    document.getElementById("note")
    .value = "";

    document.getElementById("image")
    .value = "";

    editIndex = -1;

}


// SECURITY
function escapeHTML(text){

    return text

    .replace(/&/g,"&amp;")

    .replace(/</g,"&lt;")

    .replace(/>/g,"&gt;")

    .replace(/"/g,"&quot;")

    .replace(/'/g,"&#039;");

}


// START
showDesigns();

</script>

</body>
</html><!-- CONTACT -->
<div class="card contact">

    <h2>📞 Contact Me</h2>

    <a href="tel:09989976474" class="contact-btn">
        📞 Call Me
    </a>

    <a href="mailto:zawwinthein83111k@gmail.com" class="contact-btn email">
        📧 Email Me
    </a>

</div>
