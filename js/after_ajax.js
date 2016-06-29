
(function ($) {
    Drupal.behaviors.afterAjax = {
        attach: function (context, settings) {    
            var form = $("#dayscript-form");
            var validate_rules = {
                username: {
                    required: true,
                    validateAlphanumeric: true,
                },
                identification:{
                    required: true,
                    minlength: 4,
                    maxlength: 10,
                    number: true,
                    checkIdentification: true,
                    
                },
                work: {
                    required: true,
                }
            };
            var validate_messages = {
                username:{
                    required: 'El campo nombre es obligatorio', 
                    validateAlphanumeric: 'El campo nombre solo acepta caracteres alfanumericos', 
                },
                identification:{
                    required: 'El campo identificación es obligatorio',
                    checkIdentification: "El número de identificación ingresado ya existe.",
                    minlength: 'El campo identificación debe contener mínimo 4 caracteres',
                    maxlength: 'El campo identificación debe contener maximo 10 caracteres',
                    number: 'El campo identificación solo acepta caracteres numericos',
                },
                work: {
                    required: 'El campo de fecha de nacimiento es obligatorio',
                },
            };
            form.validate({
                rules: validate_rules,
                messages: validate_messages,
            });

            $.validator.addMethod("checkIdentification", function(value, element) {
                var result = false;
                    $.ajax({
                        type:"POST",
                        async: false,
                        dataType: 'json',
                        url: Drupal.settings.basePath + "verified/identification",
                        data: {"identification" : value},
                        success: function(data) {
                            console.log(data);
                            result = (data.response == true) ? true : false;
                        }
                    });
                // return true if username is exist in database
                return result;
            });  
            $.validator.addMethod("validateAlphanumeric", function(value, element) {
                    var pattern = new RegExp(/^[a-zA-Z]+[a-zA-Z0-9._]+$/);
                    var response = pattern.test(value);
                    
                    return response;
            });
        }        
    };    
})(jQuery);
  