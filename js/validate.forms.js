jQuery(document).ready(function($) {
    
    $(function() {
        var form = $("#registerForm");
        var validate_rules = {
            name: {
                required: true,
            },
            lastname:{
                required: true,
            },
            email:{
                required: true,
                validateDuplicateEmail: true,
                email: true,
            },
            password:{
                required: true,
                minlength: 6,
            },
        };
        var validate_messages = {
            name:{
                required: 'El campo nombre es obligatorio',  
            },
            lastname:{
                required: 'El campo apellido es obligatorio',
            },
            email:{
                required: 'El campo email es obligatorio',
                validateDuplicateEmail: 'El email ya se encuentra en uso',
                email: 'Tu correo no es válido.',
            },
            password:{
                required: 'El campo contraseña es obligatorio',
                minlength: "La contraseña debe tener mínimo 6 caracteres",
            },
        };
        form.validate({
            rules: validate_rules,
            messages: validate_messages,
        });
      
        $.validator.addMethod("validateDuplicateEmail", function(value, element) {
            var url = 'validate_email.php';
            var result = false;
            $.ajax({
                type:"POST",
                async: false,
                url: url,
                data: ('email='+value),
                success: function(data) {
                    result = data == true ? true : false;
                    console.log('The ajax email result is = '+result);
                }
            });  
            return result;
        });   

    });
    
    $(function() {
        var form = $("#loginForm");
        var validate_rules = {
            email:{
                required: true,
                email: true,
            },
            password:{
                required: true,
                validateLogin: true,
                minlength: 6,
            },
        };
        var validate_messages = {
            email:{
                required: 'El campo email es obligatorio',
                email: 'Tu correo no es válido.',
            },
            password:{
                required: 'El campo contraseña es obligatorio',
                minlength: "La contraseña debe tener mínimo 6 caracteres",
                validateLogin: 'Usuario o contraseña no valido.',
            },
        };
        form.validate({
            rules: validate_rules,
            messages: validate_messages,
        }); 

        $.validator.addMethod("validateLogin", function(e) {
            var url = 'validate_login.php';
            var result = false;
            $.ajax({
                type:"POST",
                async: false,
                url: url,
                data: $('#loginForm').serialize(),
                success: function(data) {
                    result = data == true ? true : false;
                    console.log('The ajax email result is = '+result);
                }
            });  
            return result;
        });       
    });    
    
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      ++ script para manejo de validación con ajax por medio de evento click  ++
      ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    $( "#login" ).on('click',function(e) {
        e.preventDefault();
        console.log('succes event click');
        var email = $('#email').val();
        var password = $('#password').val();

        $.ajax({
            type: 'post',
            url: 'login.php',
            data: ('email='+email+'&password='+password),
            success: function(data) {
                console.log('The data is: '+data);
                if(data==false) {
                    $('#message-error').html('Error');
                }  
            }
        });
    });*/
    
});