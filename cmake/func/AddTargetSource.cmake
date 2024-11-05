# Helper function to add headers to the global source list
function(brk_add_headers)
    # Append all the passed arguments (headers) to the target's sources
    target_sources(${PROJECT_NAME} PUBLIC "${ARGV}")
endfunction()

# Helper function to add headers to the global source list
function(brk_add_sources)
    # Append all the passed arguments (headers) to the target's sources
    target_sources(${PROJECT_NAME} PRIVATE "${ARGV}")
endfunction()
